#include <functional>
#include <format>
#include "cpu.hpp"
#include "disasm.hpp"

#ifndef __DISASM_TABLE_HPP__
#define __DISASM_TABLE_HPP__

using namespace cpu;
using namespace std;
namespace cpu
{
  namespace opcode
  {
    static const array<std::function<std::string(cpu &)>, 256> disasm_cb_table = {
        /* 00 */ [](cpu &pCpu)
        { return "rlc b"; },
        /* 01 */ [](cpu &pCpu)
        { return "rlc c"; },
        /* 02 */ [](cpu &pCpu)
        { return "rlc d"; },
        /* 03 */ [](cpu &pCpu)
        { return "rlc e"; },
        /* 04 */ [](cpu &pCpu)
        { return "rlc h"; },
        /* 05 */ [](cpu &pCpu)
        { return "rlc l"; },
        /* 06 */ [](cpu &pCpu)
        { return "rlc (hl)"; },
        /* 07 */ [](cpu &pCpu)
        { return "rlc a"; },
        /* 08 */ [](cpu &pCpu)
        { return "rrc b"; },
        /* 09 */ [](cpu &pCpu)
        { return "rrc c"; },
        /* 0a */ [](cpu &pCpu)
        { return "rrc d"; },
        /* 0b */ [](cpu &pCpu)
        { return "rrc e"; },
        /* 0c */ [](cpu &pCpu)
        { return "rrc h"; },
        /* 0d */ [](cpu &pCpu)
        { return "rrc l"; },
        /* 0e */ [](cpu &pCpu)
        { return "rrc (hl)"; },
        /* 0f */ [](cpu &pCpu)
        { return "rrc a"; },
        /* 10 */ [](cpu &pCpu)
        { return "rl b"; },
        /* 11 */ [](cpu &pCpu)
        { return "rl c"; },
        /* 12 */ [](cpu &pCpu)
        { return "rl d"; },
        /* 13 */ [](cpu &pCpu)
        { return "rl e"; },
        /* 14 */ [](cpu &pCpu)
        { return "rl h"; },
        /* 15 */ [](cpu &pCpu)
        { return "rl l"; },
        /* 16 */ [](cpu &pCpu)
        { return "rl (hl)"; },
        /* 17 */ [](cpu &pCpu)
        { return "rl a"; },
        /* 18 */ [](cpu &pCpu)
        { return "rr b"; },
        /* 19 */ [](cpu &pCpu)
        { return "rr c"; },
        /* 1a */ [](cpu &pCpu)
        { return "rr d"; },
        /* 1b */ [](cpu &pCpu)
        { return "rr e"; },
        /* 1c */ [](cpu &pCpu)
        { return "rr h"; },
        /* 1d */ [](cpu &pCpu)
        { return "rr l"; },
        /* 1e */ [](cpu &pCpu)
        { return "rr (hl)"; },
        /* 1f */ [](cpu &pCpu)
        { return "rr a"; },
        /* 20 */ [](cpu &pCpu)
        { return "sla b"; },
        /* 21 */ [](cpu &pCpu)
        { return "sla c"; },
        /* 22 */ [](cpu &pCpu)
        { return "sla d"; },
        /* 23 */ [](cpu &pCpu)
        { return "sla e"; },
        /* 24 */ [](cpu &pCpu)
        { return "sla h"; },
        /* 25 */ [](cpu &pCpu)
        { return "sla l"; },
        /* 26 */ [](cpu &pCpu)
        { return "sla (hl)"; },
        /* 27 */ [](cpu &pCpu)
        { return "sla a"; },
        /* 28 */ [](cpu &pCpu)
        { return "sra b"; },
        /* 29 */ [](cpu &pCpu)
        { return "sra c"; },
        /* 2a */ [](cpu &pCpu)
        { return "sra d"; },
        /* 2b */ [](cpu &pCpu)
        { return "sra e"; },
        /* 2c */ [](cpu &pCpu)
        { return "sra h"; },
        /* 2d */ [](cpu &pCpu)
        { return "sra l"; },
        /* 2e */ [](cpu &pCpu)
        { return "sra (hl)"; },
        /* 2f */ [](cpu &pCpu)
        { return "sra a"; },
        /* 30 */ [](cpu &pCpu)
        { return "swap b"; },
        /* 31 */ [](cpu &pCpu)
        { return "swap c"; },
        /* 32 */ [](cpu &pCpu)
        { return "swap d"; },
        /* 33 */ [](cpu &pCpu)
        { return "swap e"; },
        /* 34 */ [](cpu &pCpu)
        { return "swap h"; },
        /* 35 */ [](cpu &pCpu)
        { return "swap l"; },
        /* 36 */ [](cpu &pCpu)
        { return "swap (hl)"; },
        /* 37 */ [](cpu &pCpu)
        { return "swap a"; },
        /* 38 */ [](cpu &pCpu)
        { return "srl b"; },
        /* 39 */ [](cpu &pCpu)
        { return "srl c"; },
        /* 3a */ [](cpu &pCpu)
        { return "srl d"; },
        /* 3b */ [](cpu &pCpu)
        { return "srl e"; },
        /* 3c */ [](cpu &pCpu)
        { return "srl h"; },
        /* 3d */ [](cpu &pCpu)
        { return "srl l"; },
        /* 3e */ [](cpu &pCpu)
        { return "srl (hl)"; },
        /* 3f */ [](cpu &pCpu)
        { return "srl a"; },
        /* 40 */ [](cpu &pCpu)
        { return "bit 0, b"; },
        /* 41 */ [](cpu &pCpu)
        { return "bit 0, c"; },
        /* 42 */ [](cpu &pCpu)
        { return "bit 0, d"; },
        /* 43 */ [](cpu &pCpu)
        { return "bit 0, e"; },
        /* 44 */ [](cpu &pCpu)
        { return "bit 0, h"; },
        /* 45 */ [](cpu &pCpu)
        { return "bit 0, l"; },
        /* 46 */ [](cpu &pCpu)
        { return "bit 0, (hl)"; },
        /* 47 */ [](cpu &pCpu)
        { return "bit 0, a"; },
        /* 48 */ [](cpu &pCpu)
        { return "bit 1, b"; },
        /* 49 */ [](cpu &pCpu)
        { return "bit 1, c"; },
        /* 4a */ [](cpu &pCpu)
        { return "bit 1, d"; },
        /* 4b */ [](cpu &pCpu)
        { return "bit 1, e"; },
        /* 4c */ [](cpu &pCpu)
        { return "bit 1, h"; },
        /* 4d */ [](cpu &pCpu)
        { return "bit 1, l"; },
        /* 4e */ [](cpu &pCpu)
        { return "bit 1, (hl)"; },
        /* 4f */ [](cpu &pCpu)
        { return "bit 1, a"; },
        /* 50 */ [](cpu &pCpu)
        { return "bit 2, b"; },
        /* 51 */ [](cpu &pCpu)
        { return "bit 2, c"; },
        /* 52 */ [](cpu &pCpu)
        { return "bit 2, d"; },
        /* 53 */ [](cpu &pCpu)
        { return "bit 2, e"; },
        /* 54 */ [](cpu &pCpu)
        { return "bit 2, h"; },
        /* 55 */ [](cpu &pCpu)
        { return "bit 2, l"; },
        /* 56 */ [](cpu &pCpu)
        { return "bit 2, (hl)"; },
        /* 57 */ [](cpu &pCpu)
        { return "bit 2, a"; },
        /* 58 */ [](cpu &pCpu)
        { return "bit 3, b"; },
        /* 59 */ [](cpu &pCpu)
        { return "bit 3, c"; },
        /* 5a */ [](cpu &pCpu)
        { return "bit 3, d"; },
        /* 5b */ [](cpu &pCpu)
        { return "bit 3, e"; },
        /* 5c */ [](cpu &pCpu)
        { return "bit 3, h"; },
        /* 5d */ [](cpu &pCpu)
        { return "bit 3, l"; },
        /* 5e */ [](cpu &pCpu)
        { return "bit 3, (hl)"; },
        /* 5f */ [](cpu &pCpu)
        { return "bit 3, a"; },
        /* 60 */ [](cpu &pCpu)
        { return "bit 4, b"; },
        /* 61 */ [](cpu &pCpu)
        { return "bit 4, c"; },
        /* 62 */ [](cpu &pCpu)
        { return "bit 4, d"; },
        /* 63 */ [](cpu &pCpu)
        { return "bit 4, e"; },
        /* 64 */ [](cpu &pCpu)
        { return "bit 4, h"; },
        /* 65 */ [](cpu &pCpu)
        { return "bit 4, l"; },
        /* 66 */ [](cpu &pCpu)
        { return "bit 4, (hl)"; },
        /* 67 */ [](cpu &pCpu)
        { return "bit 4, a"; },
        /* 68 */ [](cpu &pCpu)
        { return "bit 5, b"; },
        /* 69 */ [](cpu &pCpu)
        { return "bit 5, c"; },
        /* 6a */ [](cpu &pCpu)
        { return "bit 5, d"; },
        /* 6b */ [](cpu &pCpu)
        { return "bit 5, e"; },
        /* 6c */ [](cpu &pCpu)
        { return "bit 5, h"; },
        /* 6d */ [](cpu &pCpu)
        { return "bit 5, l"; },
        /* 6e */ [](cpu &pCpu)
        { return "bit 5, (hl)"; },
        /* 6f */ [](cpu &pCpu)
        { return "bit 5, a"; },
        /* 70 */ [](cpu &pCpu)
        { return "bit 6, b"; },
        /* 71 */ [](cpu &pCpu)
        { return "bit 6, c"; },
        /* 72 */ [](cpu &pCpu)
        { return "bit 6, d"; },
        /* 73 */ [](cpu &pCpu)
        { return "bit 6, e"; },
        /* 74 */ [](cpu &pCpu)
        { return "bit 6, h"; },
        /* 75 */ [](cpu &pCpu)
        { return "bit 6, l"; },
        /* 76 */ [](cpu &pCpu)
        { return "bit 6, (hl)"; },
        /* 77 */ [](cpu &pCpu)
        { return "bit 6, a"; },
        /* 78 */ [](cpu &pCpu)
        { return "bit 7, b"; },
        /* 79 */ [](cpu &pCpu)
        { return "bit 7, c"; },
        /* 7a */ [](cpu &pCpu)
        { return "bit 7, d"; },
        /* 7b */ [](cpu &pCpu)
        { return "bit 7, e"; },
        /* 7c */ [](cpu &pCpu)
        { return "bit 7, h"; },
        /* 7d */ [](cpu &pCpu)
        { return "bit 7, l"; },
        /* 7e */ [](cpu &pCpu)
        { return "bit 7, (hl)"; },
        /* 7f */ [](cpu &pCpu)
        { return "bit 7, a"; },
        /* 80 */ [](cpu &pCpu)
        { return "res 0, b"; },
        /* 81 */ [](cpu &pCpu)
        { return "res 0, c"; },
        /* 82 */ [](cpu &pCpu)
        { return "res 0, d"; },
        /* 83 */ [](cpu &pCpu)
        { return "res 0, e"; },
        /* 84 */ [](cpu &pCpu)
        { return "res 0, h"; },
        /* 85 */ [](cpu &pCpu)
        { return "res 0, l"; },
        /* 86 */ [](cpu &pCpu)
        { return "res 0, (hl)"; },
        /* 87 */ [](cpu &pCpu)
        { return "res 0, a"; },
        /* 88 */ [](cpu &pCpu)
        { return "res 1, b"; },
        /* 89 */ [](cpu &pCpu)
        { return "res 1, c"; },
        /* 8a */ [](cpu &pCpu)
        { return "res 1, d"; },
        /* 8b */ [](cpu &pCpu)
        { return "res 1, e"; },
        /* 8c */ [](cpu &pCpu)
        { return "res 1, h"; },
        /* 8d */ [](cpu &pCpu)
        { return "res 1, l"; },
        /* 8e */ [](cpu &pCpu)
        { return "res 1, (hl)"; },
        /* 8f */ [](cpu &pCpu)
        { return "res 1, a"; },
        /* 90 */ [](cpu &pCpu)
        { return "res 2, b"; },
        /* 91 */ [](cpu &pCpu)
        { return "res 2, c"; },
        /* 92 */ [](cpu &pCpu)
        { return "res 2, d"; },
        /* 93 */ [](cpu &pCpu)
        { return "res 2, e"; },
        /* 94 */ [](cpu &pCpu)
        { return "res 2, h"; },
        /* 95 */ [](cpu &pCpu)
        { return "res 2, l"; },
        /* 96 */ [](cpu &pCpu)
        { return "res 2, (hl)"; },
        /* 97 */ [](cpu &pCpu)
        { return "res 2, a"; },
        /* 98 */ [](cpu &pCpu)
        { return "res 3, b"; },
        /* 99 */ [](cpu &pCpu)
        { return "res 3, c"; },
        /* 9a */ [](cpu &pCpu)
        { return "res 3, d"; },
        /* 9b */ [](cpu &pCpu)
        { return "res 3, e"; },
        /* 9c */ [](cpu &pCpu)
        { return "res 3, h"; },
        /* 9d */ [](cpu &pCpu)
        { return "res 3, l"; },
        /* 9e */ [](cpu &pCpu)
        { return "res 3, (hl)"; },
        /* 9f */ [](cpu &pCpu)
        { return "res 3, a"; },
        /* a0 */ [](cpu &pCpu)
        { return "res 4, b"; },
        /* a1 */ [](cpu &pCpu)
        { return "res 4, c"; },
        /* a2 */ [](cpu &pCpu)
        { return "res 4, d"; },
        /* a3 */ [](cpu &pCpu)
        { return "res 4, e"; },
        /* a4 */ [](cpu &pCpu)
        { return "res 4, h"; },
        /* a5 */ [](cpu &pCpu)
        { return "res 4, l"; },
        /* a6 */ [](cpu &pCpu)
        { return "res 4, (hl)"; },
        /* a7 */ [](cpu &pCpu)
        { return "res 4, a"; },
        /* a8 */ [](cpu &pCpu)
        { return "res 5, b"; },
        /* a9 */ [](cpu &pCpu)
        { return "res 5, c"; },
        /* aa */ [](cpu &pCpu)
        { return "res 5, d"; },
        /* ab */ [](cpu &pCpu)
        { return "res 5, e"; },
        /* ac */ [](cpu &pCpu)
        { return "res 5, h"; },
        /* ad */ [](cpu &pCpu)
        { return "res 5, l"; },
        /* ae */ [](cpu &pCpu)
        { return "res 5, (hl)"; },
        /* af */ [](cpu &pCpu)
        { return "res 5, a"; },
        /* b0 */ [](cpu &pCpu)
        { return "res 6, b"; },
        /* b1 */ [](cpu &pCpu)
        { return "res 6, c"; },
        /* b2 */ [](cpu &pCpu)
        { return "res 6, d"; },
        /* b3 */ [](cpu &pCpu)
        { return "res 6, e"; },
        /* b4 */ [](cpu &pCpu)
        { return "res 6, h"; },
        /* b5 */ [](cpu &pCpu)
        { return "res 6, l"; },
        /* b6 */ [](cpu &pCpu)
        { return "res 6, (hl)"; },
        /* b7 */ [](cpu &pCpu)
        { return "res 6, a"; },
        /* b8 */ [](cpu &pCpu)
        { return "res 7, b"; },
        /* b9 */ [](cpu &pCpu)
        { return "res 7, c"; },
        /* ba */ [](cpu &pCpu)
        { return "res 7, d"; },
        /* bb */ [](cpu &pCpu)
        { return "res 7, e"; },
        /* bc */ [](cpu &pCpu)
        { return "res 7, h"; },
        /* bd */ [](cpu &pCpu)
        { return "res 7, l"; },
        /* be */ [](cpu &pCpu)
        { return "res 7, (hl)"; },
        /* bf */ [](cpu &pCpu)
        { return "res 7, a"; },
        /* c0 */ [](cpu &pCpu)
        { return "set 0, b"; },
        /* c1 */ [](cpu &pCpu)
        { return "set 0, c"; },
        /* c2 */ [](cpu &pCpu)
        { return "set 0, d"; },
        /* c3 */ [](cpu &pCpu)
        { return "set 0, e"; },
        /* c4 */ [](cpu &pCpu)
        { return "set 0, h"; },
        /* c5 */ [](cpu &pCpu)
        { return "set 0, l"; },
        /* c6 */ [](cpu &pCpu)
        { return "set 0, (hl)"; },
        /* c7 */ [](cpu &pCpu)
        { return "set 0, a"; },
        /* c8 */ [](cpu &pCpu)
        { return "set 1, b"; },
        /* c9 */ [](cpu &pCpu)
        { return "set 1, c"; },
        /* ca */ [](cpu &pCpu)
        { return "set 1, d"; },
        /* cb */ [](cpu &pCpu)
        { return "set 1, e"; },
        /* cc */ [](cpu &pCpu)
        { return "set 1, h"; },
        /* cd */ [](cpu &pCpu)
        { return "set 1, l"; },
        /* ce */ [](cpu &pCpu)
        { return "set 1, (hl)"; },
        /* cf */ [](cpu &pCpu)
        { return "set 1, a"; },
        /* d0 */ [](cpu &pCpu)
        { return "set 2, b"; },
        /* d1 */ [](cpu &pCpu)
        { return "set 2, c"; },
        /* d2 */ [](cpu &pCpu)
        { return "set 2, d"; },
        /* d3 */ [](cpu &pCpu)
        { return "set 2, e"; },
        /* d4 */ [](cpu &pCpu)
        { return "set 2, h"; },
        /* d5 */ [](cpu &pCpu)
        { return "set 2, l"; },
        /* d6 */ [](cpu &pCpu)
        { return "set 2, (hl)"; },
        /* d7 */ [](cpu &pCpu)
        { return "set 2, a"; },
        /* d8 */ [](cpu &pCpu)
        { return "set 3, b"; },
        /* d9 */ [](cpu &pCpu)
        { return "set 3, c"; },
        /* da */ [](cpu &pCpu)
        { return "set 3, d"; },
        /* db */ [](cpu &pCpu)
        { return "set 3, e"; },
        /* dc */ [](cpu &pCpu)
        { return "set 3, h"; },
        /* dd */ [](cpu &pCpu)
        { return "set 3, l"; },
        /* de */ [](cpu &pCpu)
        { return "set 3, (hl)"; },
        /* df */ [](cpu &pCpu)
        { return "set 3, a"; },
        /* e0 */ [](cpu &pCpu)
        { return "set 4, b"; },
        /* e1 */ [](cpu &pCpu)
        { return "set 4, c"; },
        /* e2 */ [](cpu &pCpu)
        { return "set 4, d"; },
        /* e3 */ [](cpu &pCpu)
        { return "set 4, e"; },
        /* e4 */ [](cpu &pCpu)
        { return "set 4, h"; },
        /* e5 */ [](cpu &pCpu)
        { return "set 4, l"; },
        /* e6 */ [](cpu &pCpu)
        { return "set 4, (hl)"; },
        /* e7 */ [](cpu &pCpu)
        { return "set 4, a"; },
        /* e8 */ [](cpu &pCpu)
        { return "set 5, b"; },
        /* e9 */ [](cpu &pCpu)
        { return "set 5, c"; },
        /* ea */ [](cpu &pCpu)
        { return "set 5, d"; },
        /* eb */ [](cpu &pCpu)
        { return "set 5, e"; },
        /* ec */ [](cpu &pCpu)
        { return "set 5, h"; },
        /* ed */ [](cpu &pCpu)
        { return "set 5, l"; },
        /* ee */ [](cpu &pCpu)
        { return "set 5, (hl)"; },
        /* ef */ [](cpu &pCpu)
        { return "set 5, a"; },
        /* f0 */ [](cpu &pCpu)
        { return "set 6, b"; },
        /* f1 */ [](cpu &pCpu)
        { return "set 6, c"; },
        /* f2 */ [](cpu &pCpu)
        { return "set 6, d"; },
        /* f3 */ [](cpu &pCpu)
        { return "set 6, e"; },
        /* f4 */ [](cpu &pCpu)
        { return "set 6, h"; },
        /* f5 */ [](cpu &pCpu)
        { return "set 6, l"; },
        /* f6 */ [](cpu &pCpu)
        { return "set 6, (hl)"; },
        /* f7 */ [](cpu &pCpu)
        { return "set 6, a"; },
        /* f8 */ [](cpu &pCpu)
        { return "set 7, b"; },
        /* f9 */ [](cpu &pCpu)
        { return "set 7, c"; },
        /* fa */ [](cpu &pCpu)
        { return "set 7, d"; },
        /* fb */ [](cpu &pCpu)
        { return "set 7, e"; },
        /* fc */ [](cpu &pCpu)
        { return "set 7, h"; },
        /* fd */ [](cpu &pCpu)
        { return "set 7, l"; },
        /* fe */ [](cpu &pCpu)
        { return "set 7, (hl)"; },
        /* ff */ [](cpu &pCpu)
        { return "set 7, a"; },
    };
    static const array<std::function<std::string(cpu &)>, 256> disasm_main_table = {
        /* 00 */ [](cpu &pCpu)
        { return "nop"; },
        /* 01 */ [](cpu &pCpu)
        { return std::format("ld bc, ${:04x}", pCpu.readp_next16()); },
        /* 02 */ [](cpu &pCpu)
        { return "ld (bc), a"; },
        /* 03 */ [](cpu &pCpu)
        { return "inc bc"; },
        /* 04 */ [](cpu &pCpu)
        { return "inc b"; },
        /* 05 */ [](cpu &pCpu)
        { return "dec b"; },
        /* 06 */ [](cpu &pCpu)
        { return std::format("ld b ${:x}", pCpu.readp_next8()); },
        /* 07 */ [](cpu &pCpu)
        { return "rlca"; },
        /* 08 */ [](cpu &pCpu)
        { return std::format("ld (${:04x}), sp", pCpu.readp_next16()); },
        /* 09 */ [](cpu &pCpu)
        { return "add hl, bc"; },
        /* 0a */ [](cpu &pCpu)
        { return "ld a, (bc)"; },
        /* 0b */ [](cpu &pCpu)
        { return "dec bc"; },
        /* 0c */ [](cpu &pCpu)
        { return "inc c"; },
        /* 0d */ [](cpu &pCpu)
        { return "dec c"; },
        /* 0e */ [](cpu &pCpu)
        { return std::format("ld c ${:x}", pCpu.readp_next8()); },
        /* 0f */ [](cpu &pCpu)
        { return "rrca"; },
        /* 10 */ [](cpu &pCpu)
        { return "stop"; },
        /* 11 */ [](cpu &pCpu)
        { return std::format("ld de, ${:04x}", pCpu.readp_next16()); },
        /* 12 */ [](cpu &pCpu)
        { return "ld (de), a"; },
        /* 13 */ [](cpu &pCpu)
        { return "inc de"; },
        /* 14 */ [](cpu &pCpu)
        { return "inc d"; },
        /* 15 */ [](cpu &pCpu)
        { return "dec d"; },
        /* 16 */ [](cpu &pCpu)
        { return std::format("ld d ${:x}", pCpu.readp_next8()); },
        /* 17 */ [](cpu &pCpu)
        { return "rla"; },
        /* 18 */ [](cpu &pCpu)
        { return std::format("jr ${:x}", pCpu.readp_nextr8()); },
        /* 19 */ [](cpu &pCpu)
        { return "add hl, de"; },
        /* 1a */ [](cpu &pCpu)
        { return "ld a, (de)"; },
        /* 1b */ [](cpu &pCpu)
        { return "dec de"; },
        /* 1c */ [](cpu &pCpu)
        { return "inc e"; },
        /* 1d */ [](cpu &pCpu)
        { return "dec e"; },
        /* 1e */ [](cpu &pCpu)
        { return std::format("ld e ${:x}", pCpu.readp_next8()); },
        /* 1f */ [](cpu &pCpu)
        { return "rra"; },
        /* 20 */ [](cpu &pCpu)
        { return std::format("jr nz, ${:x}", pCpu.readp_next8()); },
        /* 21 */ [](cpu &pCpu)
        { return std::format("ld hl, ${:04x}", pCpu.readp_next16()); },
        /* 22 */ [](cpu &pCpu)
        { return "ld (hl+), a"; },
        /* 23 */ [](cpu &pCpu)
        { return "inc hl"; },
        /* 24 */ [](cpu &pCpu)
        { return "inc h"; },
        /* 25 */ [](cpu &pCpu)
        { return "dec h"; },
        /* 26 */ [](cpu &pCpu)
        { return std::format("ld h ${:x}", pCpu.readp_next8()); },
        /* 27 */ [](cpu &pCpu)
        { return "daa"; },
        /* 28 */ [](cpu &pCpu)
        { return std::format("jr z, ${:x}", pCpu.readp_next8()); },
        /* 29 */ [](cpu &pCpu)
        { return "add hl, hl"; },
        /* 2a */ [](cpu &pCpu)
        { return "ld a, (hl+)"; },
        /* 2b */ [](cpu &pCpu)
        { return "dec hl"; },
        /* 2c */ [](cpu &pCpu)
        { return "inc l"; },
        /* 2d */ [](cpu &pCpu)
        { return "dec l"; },
        /* 2e */ [](cpu &pCpu)
        { return std::format("ld l ${:x}", pCpu.readp_next8()); },
        /* 2f */ [](cpu &pCpu)
        { return "cpl"; },
        /* 30 */ [](cpu &pCpu)
        { return std::format("jr nc, ${:x}", pCpu.readp_next8()); },
        /* 31 */ [](cpu &pCpu)
        { return std::format("ld sp, ${:04x}", pCpu.readp_next16()); },
        /* 32 */ [](cpu &pCpu)
        { return "ld (hl-), a"; },
        /* 33 */ [](cpu &pCpu)
        { return "inc sp"; },
        /* 34 */ [](cpu &pCpu)
        { return "inc (hl)"; },
        /* 35 */ [](cpu &pCpu)
        { return "dec (hl)"; },
        /* 36 */ [](cpu &pCpu)
        { return std::format("ld (hl) ${:x}", pCpu.readp_next8()); },
        /* 37 */ [](cpu &pCpu)
        { return "scf"; },
        /* 38 */ [](cpu &pCpu)
        { return std::format("jr c, ${:x}", pCpu.readp_next8()); },
        /* 39 */ [](cpu &pCpu)
        { return "add hl, sp"; },
        /* 3a */ [](cpu &pCpu)
        { return "ld a, (hl-)"; },
        /* 3b */ [](cpu &pCpu)
        { return "dec sp"; },
        /* 3c */ [](cpu &pCpu)
        { return "inc a"; },
        /* 3d */ [](cpu &pCpu)
        { return "dec a"; },
        /* 3e */ [](cpu &pCpu)
        { return std::format("ld a ${:x}", pCpu.readp_next8()); },
        /* 3f */ [](cpu &pCpu)
        { return "ccf"; },
        /* 40 */ [](cpu &pCpu)
        { return "ld b, b"; },
        /* 41 */ [](cpu &pCpu)
        { return "ld b, c"; },
        /* 42 */ [](cpu &pCpu)
        { return "ld b, d"; },
        /* 43 */ [](cpu &pCpu)
        { return "ld b, e"; },
        /* 44 */ [](cpu &pCpu)
        { return "ld b, h"; },
        /* 45 */ [](cpu &pCpu)
        { return "ld b, l"; },
        /* 46 */ [](cpu &pCpu)
        { return "ld b, (hl)"; },
        /* 47 */ [](cpu &pCpu)
        { return "ld b, a"; },
        /* 48 */ [](cpu &pCpu)
        { return "ld c, b"; },
        /* 49 */ [](cpu &pCpu)
        { return "ld c, c"; },
        /* 4a */ [](cpu &pCpu)
        { return "ld c, d"; },
        /* 4b */ [](cpu &pCpu)
        { return "ld c, e"; },
        /* 4c */ [](cpu &pCpu)
        { return "ld c, h"; },
        /* 4d */ [](cpu &pCpu)
        { return "ld c, l"; },
        /* 4e */ [](cpu &pCpu)
        { return "ld c, (hl)"; },
        /* 4f */ [](cpu &pCpu)
        { return "ld c, a"; },
        /* 50 */ [](cpu &pCpu)
        { return "ld d, b"; },
        /* 51 */ [](cpu &pCpu)
        { return "ld d, c"; },
        /* 52 */ [](cpu &pCpu)
        { return "ld d, d"; },
        /* 53 */ [](cpu &pCpu)
        { return "ld d, e"; },
        /* 54 */ [](cpu &pCpu)
        { return "ld d, h"; },
        /* 55 */ [](cpu &pCpu)
        { return "ld d, l"; },
        /* 56 */ [](cpu &pCpu)
        { return "ld d, (hl)"; },
        /* 57 */ [](cpu &pCpu)
        { return "ld d, a"; },
        /* 58 */ [](cpu &pCpu)
        { return "ld e, b"; },
        /* 59 */ [](cpu &pCpu)
        { return "ld e, c"; },
        /* 5a */ [](cpu &pCpu)
        { return "ld e, d"; },
        /* 5b */ [](cpu &pCpu)
        { return "ld e, e"; },
        /* 5c */ [](cpu &pCpu)
        { return "ld e, h"; },
        /* 5d */ [](cpu &pCpu)
        { return "ld e, l"; },
        /* 5e */ [](cpu &pCpu)
        { return "ld e, (hl)"; },
        /* 5f */ [](cpu &pCpu)
        { return "ld e, a"; },
        /* 60 */ [](cpu &pCpu)
        { return "ld h, b"; },
        /* 61 */ [](cpu &pCpu)
        { return "ld h, c"; },
        /* 62 */ [](cpu &pCpu)
        { return "ld h, d"; },
        /* 63 */ [](cpu &pCpu)
        { return "ld h, e"; },
        /* 64 */ [](cpu &pCpu)
        { return "ld h, h"; },
        /* 65 */ [](cpu &pCpu)
        { return "ld h, l"; },
        /* 66 */ [](cpu &pCpu)
        { return "ld h, (hl)"; },
        /* 67 */ [](cpu &pCpu)
        { return "ld h, a"; },
        /* 68 */ [](cpu &pCpu)
        { return "ld l, b"; },
        /* 69 */ [](cpu &pCpu)
        { return "ld l, c"; },
        /* 6a */ [](cpu &pCpu)
        { return "ld l, d"; },
        /* 6b */ [](cpu &pCpu)
        { return "ld l, e"; },
        /* 6c */ [](cpu &pCpu)
        { return "ld l, h"; },
        /* 6d */ [](cpu &pCpu)
        { return "ld l, l"; },
        /* 6e */ [](cpu &pCpu)
        { return "ld l, (hl)"; },
        /* 6f */ [](cpu &pCpu)
        { return "ld l, a"; },
        /* 70 */ [](cpu &pCpu)
        { return "ld (hl), b"; },
        /* 71 */ [](cpu &pCpu)
        { return "ld (hl), c"; },
        /* 72 */ [](cpu &pCpu)
        { return "ld (hl), d"; },
        /* 73 */ [](cpu &pCpu)
        { return "ld (hl), e"; },
        /* 74 */ [](cpu &pCpu)
        { return "ld (hl), h"; },
        /* 75 */ [](cpu &pCpu)
        { return "ld (hl), l"; },
        /* 76 */ [](cpu &pCpu)
        { return "halt"; },
        /* 77 */ [](cpu &pCpu)
        { return "ld (hl), a"; },
        /* 78 */ [](cpu &pCpu)
        { return "ld a, b"; },
        /* 79 */ [](cpu &pCpu)
        { return "ld a, c"; },
        /* 7a */ [](cpu &pCpu)
        { return "ld a, d"; },
        /* 7b */ [](cpu &pCpu)
        { return "ld a, e"; },
        /* 7c */ [](cpu &pCpu)
        { return "ld a, h"; },
        /* 7d */ [](cpu &pCpu)
        { return "ld a, l"; },
        /* 7e */ [](cpu &pCpu)
        { return "ld a, (hl)"; },
        /* 7f */ [](cpu &pCpu)
        { return "ld a, a"; },
        /* 80 */ [](cpu &pCpu)
        { return "add b"; },
        /* 81 */ [](cpu &pCpu)
        { return "add c"; },
        /* 82 */ [](cpu &pCpu)
        { return "add d"; },
        /* 83 */ [](cpu &pCpu)
        { return "add e"; },
        /* 84 */ [](cpu &pCpu)
        { return "add h"; },
        /* 85 */ [](cpu &pCpu)
        { return "add l"; },
        /* 86 */ [](cpu &pCpu)
        { return "add (hl)"; },
        /* 87 */ [](cpu &pCpu)
        { return "add a"; },
        /* 88 */ [](cpu &pCpu)
        { return "adc b"; },
        /* 89 */ [](cpu &pCpu)
        { return "adc c"; },
        /* 8a */ [](cpu &pCpu)
        { return "adc d"; },
        /* 8b */ [](cpu &pCpu)
        { return "adc e"; },
        /* 8c */ [](cpu &pCpu)
        { return "adc h"; },
        /* 8d */ [](cpu &pCpu)
        { return "adc l"; },
        /* 8e */ [](cpu &pCpu)
        { return "adc (hl)"; },
        /* 8f */ [](cpu &pCpu)
        { return "adc a"; },
        /* 90 */ [](cpu &pCpu)
        { return "sub b"; },
        /* 91 */ [](cpu &pCpu)
        { return "sub c"; },
        /* 92 */ [](cpu &pCpu)
        { return "sub d"; },
        /* 93 */ [](cpu &pCpu)
        { return "sub e"; },
        /* 94 */ [](cpu &pCpu)
        { return "sub h"; },
        /* 95 */ [](cpu &pCpu)
        { return "sub l"; },
        /* 96 */ [](cpu &pCpu)
        { return "sub (hl)"; },
        /* 97 */ [](cpu &pCpu)
        { return "sub a"; },
        /* 98 */ [](cpu &pCpu)
        { return "sbc b"; },
        /* 99 */ [](cpu &pCpu)
        { return "sbc c"; },
        /* 9a */ [](cpu &pCpu)
        { return "sbc d"; },
        /* 9b */ [](cpu &pCpu)
        { return "sbc e"; },
        /* 9c */ [](cpu &pCpu)
        { return "sbc h"; },
        /* 9d */ [](cpu &pCpu)
        { return "sbc l"; },
        /* 9e */ [](cpu &pCpu)
        { return "sbc (hl)"; },
        /* 9f */ [](cpu &pCpu)
        { return "sbc a"; },
        /* a0 */ [](cpu &pCpu)
        { return "and b"; },
        /* a1 */ [](cpu &pCpu)
        { return "and c"; },
        /* a2 */ [](cpu &pCpu)
        { return "and d"; },
        /* a3 */ [](cpu &pCpu)
        { return "and e"; },
        /* a4 */ [](cpu &pCpu)
        { return "and h"; },
        /* a5 */ [](cpu &pCpu)
        { return "and l"; },
        /* a6 */ [](cpu &pCpu)
        { return "and (hl)"; },
        /* a7 */ [](cpu &pCpu)
        { return "and a"; },
        /* a8 */ [](cpu &pCpu)
        { return "xor b"; },
        /* a9 */ [](cpu &pCpu)
        { return "xor c"; },
        /* aa */ [](cpu &pCpu)
        { return "xor d"; },
        /* ab */ [](cpu &pCpu)
        { return "xor e"; },
        /* ac */ [](cpu &pCpu)
        { return "xor h"; },
        /* ad */ [](cpu &pCpu)
        { return "xor l"; },
        /* ae */ [](cpu &pCpu)
        { return "xor (hl)"; },
        /* af */ [](cpu &pCpu)
        { return "xor a"; },
        /* b0 */ [](cpu &pCpu)
        { return "or b"; },
        /* b1 */ [](cpu &pCpu)
        { return "or c"; },
        /* b2 */ [](cpu &pCpu)
        { return "or d"; },
        /* b3 */ [](cpu &pCpu)
        { return "or e"; },
        /* b4 */ [](cpu &pCpu)
        { return "or h"; },
        /* b5 */ [](cpu &pCpu)
        { return "or l"; },
        /* b6 */ [](cpu &pCpu)
        { return "or (hl)"; },
        /* b7 */ [](cpu &pCpu)
        { return "or a"; },
        /* b8 */ [](cpu &pCpu)
        { return "cp b"; },
        /* b9 */ [](cpu &pCpu)
        { return "cp c"; },
        /* ba */ [](cpu &pCpu)
        { return "cp d"; },
        /* bb */ [](cpu &pCpu)
        { return "cp e"; },
        /* bc */ [](cpu &pCpu)
        { return "cp h"; },
        /* bd */ [](cpu &pCpu)
        { return "cp l"; },
        /* be */ [](cpu &pCpu)
        { return "cp (hl)"; },
        /* bf */ [](cpu &pCpu)
        { return "cp a"; },
        /* c0 */ [](cpu &pCpu)
        { return "ret nz"; },
        /* c1 */ [](cpu &pCpu)
        { return "pop bc"; },
        /* c2 */ [](cpu &pCpu)
        { return std::format("jp nz, ${:04x}", pCpu.readp_next16()); },
        /* c3 */ [](cpu &pCpu)
        { return std::format("jp ${:04x}", pCpu.readp_next16()); },
        /* c4 */ [](cpu &pCpu)
        { return std::format("call nz, ${:04x}", pCpu.readp_next16()); },
        /* c5 */ [](cpu &pCpu)
        { return "push bc"; },
        /* c6 */ [](cpu &pCpu)
        { return std::format("add, ${:x}", pCpu.readp_next8()); },
        /* c7 */ [](cpu &pCpu)
        { return "rst $0"; },
        /* c8 */ [](cpu &pCpu)
        { return "ret z"; },
        /* c9 */ [](cpu &pCpu)
        { return "ret"; },
        /* ca */ [](cpu &pCpu)
        { return std::format("jp z, ${:04x}", pCpu.readp_next16()); },
        /* cb */ [](cpu &pCpu)
        { return disasm_op_cb(pCpu); },
        /* cc */ [](cpu &pCpu)
        { return std::format("call z, ${:04x}", pCpu.readp_next16()); },
        /* cd */ [](cpu &pCpu)
        { return std::format("call ${:04x}", pCpu.readp_next16()); },
        /* ce */ [](cpu &pCpu)
        { return std::format("adc, ${:x}", pCpu.readp_next8()); },
        /* cf */ [](cpu &pCpu)
        { return "rst $8"; },
        /* d0 */ [](cpu &pCpu)
        { return "ret nc"; },
        /* d1 */ [](cpu &pCpu)
        { return "pop de"; },
        /* d2 */ [](cpu &pCpu)
        { return std::format("jp nc, ${:04x}", pCpu.readp_next16()); },
        /* d3 */ [](cpu &pCpu)
        { return "nop"; },
        /* d4 */ [](cpu &pCpu)
        { return std::format("call nc, ${:04x}", pCpu.readp_next16()); },
        /* d5 */ [](cpu &pCpu)
        { return "push de"; },
        /* d6 */ [](cpu &pCpu)
        { return std::format("sub, ${:x}", pCpu.readp_next8()); },
        /* d7 */ [](cpu &pCpu)
        { return "rst $10"; },
        /* d8 */ [](cpu &pCpu)
        { return "ret c"; },
        /* d9 */ [](cpu &pCpu)
        { return "reti"; },
        /* da */ [](cpu &pCpu)
        { return std::format("jp c, ${:04x}", pCpu.readp_next16()); },
        /* db */ [](cpu &pCpu)
        { return "nop"; },
        /* dc */ [](cpu &pCpu)
        { return std::format("call c, ${:04x}", pCpu.readp_next16()); },
        /* dd */ [](cpu &pCpu)
        { return "nop"; },
        /* de */ [](cpu &pCpu)
        { return std::format("sbc, ${:x}", pCpu.readp_next8()); },
        /* df */ [](cpu &pCpu)
        { return "rst $18"; },
        /* e0 */ [](cpu &pCpu)
        { return std::format("ldh (${:02x}), a", pCpu.readp_next8()); },
        /* e1 */ [](cpu &pCpu)
        { return "pop hl"; },
        /* e2 */ [](cpu &pCpu)
        { return "ld (c), a"; },
        /* e3 */ [](cpu &pCpu)
        { return "nop"; },
        /* e4 */ [](cpu &pCpu)
        { return "nop"; },
        /* e5 */ [](cpu &pCpu)
        { return "push hl"; },
        /* e6 */ [](cpu &pCpu)
        { return std::format("and, ${:x}", pCpu.readp_next8()); },
        /* e7 */ [](cpu &pCpu)
        { return "rst $20"; },
        /* e8 */ [](cpu &pCpu)
        { return std::format("add sp, ${:02x}", pCpu.readp_nextr8()); },
        /* e9 */ [](cpu &pCpu)
        { return "jp hl"; },
        /* ea */ [](cpu &pCpu)
        { return std::format("ld (${:04x}), a", pCpu.readp_next16()); },
        /* eb */ [](cpu &pCpu)
        { return "nop"; },
        /* ec */ [](cpu &pCpu)
        { return "nop"; },
        /* ed */ [](cpu &pCpu)
        { return "nop"; },
        /* ee */ [](cpu &pCpu)
        { return std::format("xor, ${:x}", pCpu.readp_next8()); },
        /* ef */ [](cpu &pCpu)
        { return "rst $28"; },
        /* f0 */ [](cpu &pCpu)
        { return std::format("ldh a, (${:02x})", pCpu.readp_next8()); },
        /* f1 */ [](cpu &pCpu)
        { return "pop af"; },
        /* f2 */ [](cpu &pCpu)
        { return "ld a, (c)"; },
        /* f3 */ [](cpu &pCpu)
        { return "di"; },
        /* f4 */ [](cpu &pCpu)
        { return "nop"; },
        /* f5 */ [](cpu &pCpu)
        { return "push af"; },
        /* f6 */ [](cpu &pCpu)
        { return std::format("or, ${:x}", pCpu.readp_next8()); },
        /* f7 */ [](cpu &pCpu)
        { return "rst $30"; },
        /* f8 */ [](cpu &pCpu)
        { return std::format("ld hl, sp + ${:02x}", pCpu.readp_nextr8()); },
        /* f9 */ [](cpu &pCpu)
        { return "ld sp, hl"; },
        /* fa */ [](cpu &pCpu)
        { return std::format("ld a, (${:04x})", pCpu.readp_next16()); },
        /* fb */ [](cpu &pCpu)
        { return "ei"; },
        /* fc */ [](cpu &pCpu)
        { return "nop"; },
        /* fd */ [](cpu &pCpu)
        { return "nop"; },
        /* fe */ [](cpu &pCpu)
        { return std::format("cp, ${:x}", pCpu.readp_next8()); },
        /* ff */ [](cpu &pCpu)
        { return "rst $38"; },
    };

  };
};

#endif // __DISASM_TABLE_HPP__
