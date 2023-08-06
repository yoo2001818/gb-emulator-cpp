function generateLUTSingle(pattern, generator, output = []) {
  // Pattern is something like "01aaabbb"
  // 0 / 1 is constraints, and "a", "b" is variables
  // We'll simply use recursion to implement this
  const letters = pattern.split("");
  function visit(index, prev, prevVar, vars) {
    const letter = letters[index];
    let currentVars = vars;
    let currentPrevVar = prevVar;
    if (
      index === letters.length ||
      (index > 0 && letters[index - 1] !== letter)
    ) {
      const prevLetter = letters[index - 1];
      if (prevLetter !== "1" && prevLetter !== "0") {
        currentVars = { ...vars, [prevLetter]: prevVar };
        currentPrevVar = 0;
      }
    }
    if (index === letters.length) {
      output[prev] = generator(currentVars);
      return;
    }
    let current = prev << 1;
    if (letter === "1") {
      current |= 1;
      return visit(index + 1, current, currentPrevVar, currentVars);
    } else if (letter === "0") {
      return visit(index + 1, current, currentPrevVar, currentVars);
    } else {
      currentPrevVar = currentPrevVar << 1;
      visit(index + 1, current, currentPrevVar, currentVars);
      return visit(index + 1, current | 1, currentPrevVar | 1, currentVars);
    }
  }
  visit(0, 0, 0, {});
  return output;
}

function generateLUTRules(size, patterns, nop) {
  const output = Array.from({ length: size }, () => nop);
  patterns.forEach(([pattern, generator]) => {
    generateLUTSingle(pattern, generator, output);
  });
  return output;
}

function generateCode(name, table) {
  const code = [];
  code.push(
    `static const array<std::function<std::string(cpu &)>, 256> ${name} = {`
  );
  table.forEach((entry, index) => {
    const indexStr = index.toString(16).padStart(2, "0");
    code.push(`  /* ${indexStr} */ [](cpu &pCpu) { return ${entry}; },`);
  });
  code.push("};");
  return code.join("\n");
}

const r8s = ["b", "c", "d", "e", "h", "l", "(hl)", "a"];

const r16s_1 = ["bc", "de", "hl", "sp"];
const r16s_2 = ["bc", "de", "hl+", "hl-"];
const r16s_3 = ["bc", "de", "hl", "af"];

const conds = ["nz", "z", "nc", "c"];

const binary_ops = ["add", "adc", "sub", "sbc", "and", "xor", "or", "cp"];

const unary_ops = ["rlc", "rrc", "rl", "rr", "sla", "sra", "swap", "srl"];

const prefix_opcodes = generateLUTRules(
  256,
  [
    ["00ooorrr", ({ o, r }) => `"${unary_ops[o]} ${r8s[r]}"`], // (unary_op) r
    ["01nnnrrr", ({ n, r }) => `"bit ${n}, ${r8s[r]}"`], // bit n, r
    ["10nnnrrr", ({ n, r }) => `"res ${n}, ${r8s[r]}"`], // res n, r
    ["11nnnrrr", ({ n, r }) => `"set ${n}, ${r8s[r]}"`], // set n, r
  ],
  "op::nop"
);

const main_opcodes = generateLUTRules(
  256,
  [
    ["00000000", () => '"nop"'],
    ["00001000", () => 'std::format("ld (${:04x}), sp", pCpu.readp_next16())'], // ld16 (a16), SP
    ["00010000", () => '"stop"'],
    ["00011000", () => 'std::format("jr ${:02x}", pCpu.readp_nextr8())'], // jr r8
    [
      "001cc000",
      ({ c }) => `std::format("jr ${conds[c]}, \${:02x}", pCpu.readp_next8())`,
    ], // jr c, r8
    // BC, DE, HL, SP
    [
      "00RR0001",
      ({ R }) =>
        `std::format("ld ${r16s_1[R]}, \${:04x}", pCpu.readp_next16())`,
    ], // ld16 r, d16
    ["00RR1001", ({ R }) => `"add hl, ${r16s_1[R]}"`], // add16 hl, r
    ["00RR0011", ({ R }) => `"inc ${r16s_1[R]}"`], // inc16 R
    ["00RR1011", ({ R }) => `"dec ${r16s_1[R]}"`], // dec16 R
    // BC, DE, HL+, HL-
    ["00RR0010", ({ R }) => `"ld (${r16s_2[R]}), a"`], // ld16 (r), a
    ["00RR1010", ({ R }) => `"ld a, (${r16s_2[R]})"`], // ld16 a, (r)
    ["00rrr100", ({ r }) => `"inc ${r8s[r]}"`], // inc r
    ["00rrr101", ({ r }) => `"dec ${r8s[r]}"`], // dec r
    [
      "00rrr110",
      ({ r }) => `std::format("ld ${r8s[r]}, \${:02x}", pCpu.readp_next8())`,
    ], // ld r, d8
    ["00000111", () => '"rlca"'], // rlca
    ["00001111", () => '"rrca"'], // rrca
    ["00010111", () => '"rla"'], // rla
    ["00011111", () => '"rra"'], // rra
    ["00100111", () => '"daa"'],
    ["00101111", () => '"cpl"'],
    ["00110111", () => '"scf"'],
    ["00111111", () => '"ccf"'],
    ["01aaabbb", ({ a, b }) => `"ld ${r8s[a]}, ${r8s[b]}"`], // ld a, b
    ["01110110", () => '"halt"'],
    ["10ooorrr", ({ o, r }) => `"${binary_ops[o]} ${r8s[r]}"`], // (binary_op) a, r
    ["110cc000", ({ c }) => `"ret ${conds[c]}"`], // ret c
    [
      "110cc010",
      ({ c }) => `std::format("jp ${conds[c]}, \${:04x}", pCpu.readp_next16())`,
    ], // jp c, a16
    [
      "110cc100",
      ({ c }) =>
        `std::format("call ${conds[c]}, \${:04x}", pCpu.readp_next16())`,
    ], // call c, a16
    ["11000011", () => 'std::format("jp ${:04x}", pCpu.readp_next16())'], // jp a16
    ["11001001", () => '"ret"'],
    ["11011001", () => '"reti"'],
    ["11001011", () => "disasm_op_cb(pCpu)"],
    ["11001101", () => 'std::format("call ${:04x}", pCpu.readp_next16())'], // call a16
    // BC, DE, HL, AF
    ["11DD0001", ({ D }) => `"pop ${r16s_3[D]}"`], // pop D
    ["11DD0101", ({ D }) => `"push ${r16s_3[D]}"`], // push D
    [
      "11ooo110",
      ({ o }) => `std::format("${binary_ops[o]} \${:02x}", pCpu.readp_next8())`,
    ], // (binary_op) a, d8
    ["11nnn111", ({ n }) => `"rst $${(n << 3).toString(16)}"`], // rst nn
    ["11100000", () => 'std::format("ldh (${:02x}), a", pCpu.readp_next8())'], // ldh (a8), a
    ["11110000", () => 'std::format("ldh a, (${:02x})", pCpu.readp_next8())'], // ldh a, (a8)
    ["11100010", () => '"ld (c), a"'], // ld (c), a
    ["11110010", () => '"ld a, (c)"'], // ld a, (c)
    ["11101000", () => 'std::format("add sp, ${:02x}", pCpu.readp_nextr8())'], // add sp, r8
    [
      "11111000",
      () => 'std::format("ld hl, sp + ${:02x}", pCpu.readp_nextr8())',
    ], // ld hl, sp + r8
    ["11101001", () => '"jp hl"'], // jp hl
    ["11111001", () => '"ld sp, hl"'], // ld sp, hl
    ["11101010", () => 'std::format("ld (${:04x}), a", pCpu.readp_next16())'], // ld (a16), a
    ["11111010", () => 'std::format("ld a, (${:04x})", pCpu.readp_next16())'], // ld a, (a16)
    ["11110011", () => '"di"'],
    ["11111011", () => '"ei"'],
  ],
  '"nop"'
);

console.log(`
#include <functional>
#include <format>
#include "cpu.hpp"
#include "disasm.hpp"

#ifndef __DISASM_TABLE_HPP__
#define __DISASM_TABLE_HPP__

namespace cpu
{
  namespace opcode
  {
`);
console.log(generateCode("disasm_cb_table", prefix_opcodes));
console.log(generateCode("disasm_main_table", main_opcodes));
console.log(`
  };
};

#endif // __DISASM_TABLE_HPP__
`);
