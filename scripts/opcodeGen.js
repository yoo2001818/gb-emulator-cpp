function generateLUTSingle(
  pattern,
  generator,
  output = [],
) {
  // Pattern is something like "01aaabbb"
  // 0 / 1 is constraints, and "a", "b" is variables
  // We'll simply use recursion to implement this
  const letters = pattern.split('');
  function visit(
    index,
    prev,
    prevVar,
    vars,
  ) {
    const letter = letters[index];
    let currentVars = vars;
    let currentPrevVar = prevVar;
    if (
      index === letters.length ||
      (index > 0 && letters[index - 1] !== letter)
    ) {
      const prevLetter = letters[index - 1];
      if (prevLetter !== '1' && prevLetter !== '0') {
        currentVars = { ...vars, [prevLetter]: prevVar };
        currentPrevVar = 0;
      }
    }
    if (index === letters.length) {
      output[prev] = generator(currentVars);
      return;
    }
    let current = prev << 1;
    if (letter === '1') {
      current |= 1;
      return visit(index + 1, current, currentPrevVar, currentVars);
    } else if (letter === '0') {
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

function generateLUTRules(
  size,
  patterns,
  nop,
) {
  const output = Array.from({ length: size }, () => nop);
  patterns.forEach(([pattern, generator]) => {
    generateLUTSingle(pattern, generator, output);
  });
  return output;
}

function generateCode(name, table) {
  const code = [];
  code.push(`static const array<void (*)(cpu &), 256> ${name} = {`);
  table.forEach((entry, index) => {
    const indexStr = index.toString(16).padStart(2, '0');
    const entryStr = entry.includes('(') ? entry : `${entry}(pCpu)`;
    code.push(`  /* ${indexStr} */ [](cpu &pCpu) { ${entryStr}; },`);
  });
  code.push('};');
  return code.join('\n');
}

const r8s = [
  'reg::reg8_b',
  'reg::reg8_c',
  'reg::reg8_d',
  'reg::reg8_e',
  'reg::reg8_h',
  'reg::reg8_l',
  'reg::reg8_indir_hl',
  'reg::reg8_a',
];

const r16s_1 = [
  'reg::reg16_bc',
  'reg::reg16_de',
  'reg::reg16_hl',
  'reg::reg16_sp',
];
const r16s_2 = [
  'reg::reg16_bc',
  'reg::reg16_de',
  'reg::reg16_hl_inc',
  'reg::reg16_hl_dec',
];
const r16s_3 = [
  'reg::reg16_bc',
  'reg::reg16_de',
  'reg::reg16_hl',
  'reg::reg16_af',
];

const conds = [
  'cond::cond_nz',
  'cond::cond_z',
  'cond::cond_nc',
  'cond::cond_c',
];

const binary_ops = [
  'alu::op_add',
  'alu::op_adc',
  'alu::op_sub',
  'alu::op_sbc',
  'alu::op_and',
  'alu::op_xor',
  'alu::op_or',
  'alu::op_cp',
];

const unary_ops = [
  'alu::op_rlc',
  'alu::op_rrc',
  'alu::op_rl',
  'alu::op_rr',
  'alu::op_sla',
  'alu::op_sra',
  'alu::op_swap',
  'alu::op_srl',
];

const prefix_opcodes = generateLUTRules(256, [
  ['00ooorrr', ({ o, r }) => `op::alu_unary_shift<${unary_ops[o]}, ${r8s[r]}>`], // (unary_op) r
  ['01nnnrrr', ({ n, r }) => `op::alu_unary_read<alu::op_bit<${n}>, ${r8s[r]}>`], // bit n, r
  ['10nnnrrr', ({ n, r }) => `op::alu_unary<alu::op_res<${n}>, ${r8s[r]}>`], // res n, r
  ['11nnnrrr', ({ n, r }) => `op::alu_unary<alu::op_set<${n}>, ${r8s[r]}>`], // set n, r
], 'op::nop');

const main_opcodes = generateLUTRules(256, [
  ['00000000', () => 'op::nop'],
  ['00001000', () => 'op::ld16_a16_sp'], // ld16 (a16), SP
  ['00010000', () => 'op::stop'],
  ['00011000', () => 'op::jr_r8'], // jr r8
  ['001cc000', ({ c }) => `op::jr_cond_r8<${conds[c]}>`], // jr c, r8
  // BC, DE, HL, SP
  ['00RR0001', ({ R }) => `op::ld16_r16_d16<${r16s_1[R]}>`], // ld16 r, d16
  ['00RR1001', ({ R }) => `op::add16<reg::reg16_hl, ${r16s_1[R]}>`], // add16 hl, r
  ['00RR0011', ({ R }) => `op::inc16<${r16s_1[R]}>`], // inc16 R
  ['00RR1011', ({ R }) => `op::dec16<${r16s_1[R]}>`], // dec16 R
  // BC, DE, HL+, HL-
  ['00RR0010', ({ R }) => `op::ld16_r16_a<${r16s_2[R]}>`], // ld16 (r), a
  ['00RR1010', ({ R }) => `op::ld16_a_r16<${r16s_2[R]}>`], // ld16 a, (r)
  ['00rrr100', ({ r }) => `op::alu_unary<alu::op_inc, ${r8s[r]}>`], // inc r
  ['00rrr101', ({ r }) => `op::alu_unary<alu::op_dec, ${r8s[r]}>`], // dec r
  ['00rrr110', ({ r }) => `op::ld8_r_d8<${r8s[r]}>`], // ld r, d8
  ['00000111', () => `op::alu_unary<alu::op_rlc, reg::reg8_a>`], // rlca
  ['00001111', () => `op::alu_unary<alu::op_rrc, reg::reg8_a>`], // rrca
  ['00010111', () => `op::alu_unary<alu::op_rl, reg::reg8_a>`], // rla
  ['00011111', () => `op::alu_unary<alu::op_rr, reg::reg8_a>`], // rra
  ['00100111', () => 'op::daa'],
  ['00101111', () => 'op::cpl'],
  ['00110111', () => 'op::scf'],
  ['00111111', () => 'op::ccf'],
  ['01aaabbb', ({ a, b }) => `op::ld8<${r8s[a]}, ${r8s[b]}>`], // ld a, b
  ['01110110', () => 'op::halt'],
  ['10ooorrr', ({ o, r }) => `op::alu_binary<${binary_ops[o]}, ${r8s[r]}>`], // (binary_op) a, r
  ['110cc000', ({ c }) => `op::ret_cond<${conds[c]}>`], // ret c
  ['110cc010', ({ c }) => `op::jp_cond_a16<${conds[c]}>`], // jp c, a16
  ['110cc100', ({ c }) => `op::call_cond_a16<${conds[c]}>`], // call c, a16
  ['11000011', () => 'op::jp_a16'],
  ['11001001', () => 'op::ret'],
  ['11011001', () => 'op::reti'],
  ['11001011', () => 'exec_op_cb'],
  ['11001101', () => 'op::call_a16'], // call a16
  // BC, DE, HL, AF
  ['11DD0001', ({ D }) => `op::pop16<${r16s_3[D]}>`], // pop D
  ['11DD0101', ({ D }) => `op::push16<${r16s_3[D]}>`], // push D
  ['11ooo110', ({ o }) => `op::alu_binary_imm<${binary_ops[o]}>`], // (binary_op) a, d8
  ['11nnn111', ({ n }) => `op::rst_nn(pCpu, 0x${(n << 3).toString(16)})`], // rst nn
  ['11100000', () => 'op::ldh8_a8_a'], // ldh (a8), a
  ['11110000', () => 'op::ldh8_a_a8'], // ldh a, (a8)
  ['11100010', () => 'op::ld8_c_a'], // ld (c), a
  ['11110010', () => 'op::ld8_a_c'], // ld a, (c)
  ['11101000', () => 'op::add16_sp_n'], // add sp, r8
  ['11111000', () => 'op::ld16_hl_spr8'], // ld hl, sp + r8
  ['11101001', () => 'op::jp_hl'], // jp hl
  ['11111001', () => 'op::ld16_sp_hl'], // ld sp, hl
  ['11101010', () => 'op::ld8_a16_a'], // ld (a16), a
  ['11111010', () => 'op::ld8_a_a16'], // ld a, (a16)
  ['11110011', () => 'op::di'],
  ['11111011', () => 'op::ei'],
], 'op::nop');

console.log(generateCode('opcode_cb_table', prefix_opcodes));
console.log(generateCode('opcode_main_table', main_opcodes));
