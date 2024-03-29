#include "op_alu.hpp"
#include "op_jmp.hpp"
#include "op_ld.hpp"
#include "op_misc.hpp"
#include "opcode.hpp"
#include "reg.hpp"
#include <functional>

#ifndef __OPCODE_TABLE_HPP__
#define __OPCODE_TABLE_HPP__

namespace cpu {
namespace opcode {
static const std::array<void (*)(cpu &), 256> opcode_cb_table = {
    /* 00 */ [](cpu &pCpu) {
      op::alu_unary_shift<alu::op_rlc, reg::reg8_b>(pCpu);
    },
    /* 01 */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_rlc, reg::reg8_c>(pCpu); },
    /* 02 */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_rlc, reg::reg8_d>(pCpu); },
    /* 03 */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_rlc, reg::reg8_e>(pCpu); },
    /* 04 */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_rlc, reg::reg8_h>(pCpu); },
    /* 05 */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_rlc, reg::reg8_l>(pCpu); },
    /* 06 */
    [](cpu &pCpu) {
      op::alu_unary_shift<alu::op_rlc, reg::reg8_indir_hl>(pCpu);
    },
    /* 07 */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_rlc, reg::reg8_a>(pCpu); },
    /* 08 */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_rrc, reg::reg8_b>(pCpu); },
    /* 09 */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_rrc, reg::reg8_c>(pCpu); },
    /* 0a */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_rrc, reg::reg8_d>(pCpu); },
    /* 0b */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_rrc, reg::reg8_e>(pCpu); },
    /* 0c */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_rrc, reg::reg8_h>(pCpu); },
    /* 0d */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_rrc, reg::reg8_l>(pCpu); },
    /* 0e */
    [](cpu &pCpu) {
      op::alu_unary_shift<alu::op_rrc, reg::reg8_indir_hl>(pCpu);
    },
    /* 0f */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_rrc, reg::reg8_a>(pCpu); },
    /* 10 */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_rl, reg::reg8_b>(pCpu); },
    /* 11 */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_rl, reg::reg8_c>(pCpu); },
    /* 12 */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_rl, reg::reg8_d>(pCpu); },
    /* 13 */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_rl, reg::reg8_e>(pCpu); },
    /* 14 */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_rl, reg::reg8_h>(pCpu); },
    /* 15 */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_rl, reg::reg8_l>(pCpu); },
    /* 16 */
    [](cpu &pCpu) {
      op::alu_unary_shift<alu::op_rl, reg::reg8_indir_hl>(pCpu);
    },
    /* 17 */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_rl, reg::reg8_a>(pCpu); },
    /* 18 */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_rr, reg::reg8_b>(pCpu); },
    /* 19 */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_rr, reg::reg8_c>(pCpu); },
    /* 1a */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_rr, reg::reg8_d>(pCpu); },
    /* 1b */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_rr, reg::reg8_e>(pCpu); },
    /* 1c */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_rr, reg::reg8_h>(pCpu); },
    /* 1d */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_rr, reg::reg8_l>(pCpu); },
    /* 1e */
    [](cpu &pCpu) {
      op::alu_unary_shift<alu::op_rr, reg::reg8_indir_hl>(pCpu);
    },
    /* 1f */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_rr, reg::reg8_a>(pCpu); },
    /* 20 */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_sla, reg::reg8_b>(pCpu); },
    /* 21 */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_sla, reg::reg8_c>(pCpu); },
    /* 22 */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_sla, reg::reg8_d>(pCpu); },
    /* 23 */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_sla, reg::reg8_e>(pCpu); },
    /* 24 */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_sla, reg::reg8_h>(pCpu); },
    /* 25 */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_sla, reg::reg8_l>(pCpu); },
    /* 26 */
    [](cpu &pCpu) {
      op::alu_unary_shift<alu::op_sla, reg::reg8_indir_hl>(pCpu);
    },
    /* 27 */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_sla, reg::reg8_a>(pCpu); },
    /* 28 */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_sra, reg::reg8_b>(pCpu); },
    /* 29 */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_sra, reg::reg8_c>(pCpu); },
    /* 2a */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_sra, reg::reg8_d>(pCpu); },
    /* 2b */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_sra, reg::reg8_e>(pCpu); },
    /* 2c */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_sra, reg::reg8_h>(pCpu); },
    /* 2d */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_sra, reg::reg8_l>(pCpu); },
    /* 2e */
    [](cpu &pCpu) {
      op::alu_unary_shift<alu::op_sra, reg::reg8_indir_hl>(pCpu);
    },
    /* 2f */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_sra, reg::reg8_a>(pCpu); },
    /* 30 */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_swap, reg::reg8_b>(pCpu); },
    /* 31 */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_swap, reg::reg8_c>(pCpu); },
    /* 32 */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_swap, reg::reg8_d>(pCpu); },
    /* 33 */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_swap, reg::reg8_e>(pCpu); },
    /* 34 */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_swap, reg::reg8_h>(pCpu); },
    /* 35 */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_swap, reg::reg8_l>(pCpu); },
    /* 36 */
    [](cpu &pCpu) {
      op::alu_unary_shift<alu::op_swap, reg::reg8_indir_hl>(pCpu);
    },
    /* 37 */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_swap, reg::reg8_a>(pCpu); },
    /* 38 */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_srl, reg::reg8_b>(pCpu); },
    /* 39 */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_srl, reg::reg8_c>(pCpu); },
    /* 3a */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_srl, reg::reg8_d>(pCpu); },
    /* 3b */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_srl, reg::reg8_e>(pCpu); },
    /* 3c */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_srl, reg::reg8_h>(pCpu); },
    /* 3d */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_srl, reg::reg8_l>(pCpu); },
    /* 3e */
    [](cpu &pCpu) {
      op::alu_unary_shift<alu::op_srl, reg::reg8_indir_hl>(pCpu);
    },
    /* 3f */
    [](cpu &pCpu) { op::alu_unary_shift<alu::op_srl, reg::reg8_a>(pCpu); },
    /* 40 */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<0>, reg::reg8_b>(pCpu); },
    /* 41 */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<0>, reg::reg8_c>(pCpu); },
    /* 42 */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<0>, reg::reg8_d>(pCpu); },
    /* 43 */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<0>, reg::reg8_e>(pCpu); },
    /* 44 */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<0>, reg::reg8_h>(pCpu); },
    /* 45 */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<0>, reg::reg8_l>(pCpu); },
    /* 46 */
    [](cpu &pCpu) {
      op::alu_unary_read<alu::op_bit<0>, reg::reg8_indir_hl>(pCpu);
    },
    /* 47 */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<0>, reg::reg8_a>(pCpu); },
    /* 48 */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<1>, reg::reg8_b>(pCpu); },
    /* 49 */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<1>, reg::reg8_c>(pCpu); },
    /* 4a */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<1>, reg::reg8_d>(pCpu); },
    /* 4b */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<1>, reg::reg8_e>(pCpu); },
    /* 4c */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<1>, reg::reg8_h>(pCpu); },
    /* 4d */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<1>, reg::reg8_l>(pCpu); },
    /* 4e */
    [](cpu &pCpu) {
      op::alu_unary_read<alu::op_bit<1>, reg::reg8_indir_hl>(pCpu);
    },
    /* 4f */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<1>, reg::reg8_a>(pCpu); },
    /* 50 */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<2>, reg::reg8_b>(pCpu); },
    /* 51 */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<2>, reg::reg8_c>(pCpu); },
    /* 52 */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<2>, reg::reg8_d>(pCpu); },
    /* 53 */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<2>, reg::reg8_e>(pCpu); },
    /* 54 */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<2>, reg::reg8_h>(pCpu); },
    /* 55 */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<2>, reg::reg8_l>(pCpu); },
    /* 56 */
    [](cpu &pCpu) {
      op::alu_unary_read<alu::op_bit<2>, reg::reg8_indir_hl>(pCpu);
    },
    /* 57 */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<2>, reg::reg8_a>(pCpu); },
    /* 58 */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<3>, reg::reg8_b>(pCpu); },
    /* 59 */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<3>, reg::reg8_c>(pCpu); },
    /* 5a */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<3>, reg::reg8_d>(pCpu); },
    /* 5b */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<3>, reg::reg8_e>(pCpu); },
    /* 5c */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<3>, reg::reg8_h>(pCpu); },
    /* 5d */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<3>, reg::reg8_l>(pCpu); },
    /* 5e */
    [](cpu &pCpu) {
      op::alu_unary_read<alu::op_bit<3>, reg::reg8_indir_hl>(pCpu);
    },
    /* 5f */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<3>, reg::reg8_a>(pCpu); },
    /* 60 */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<4>, reg::reg8_b>(pCpu); },
    /* 61 */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<4>, reg::reg8_c>(pCpu); },
    /* 62 */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<4>, reg::reg8_d>(pCpu); },
    /* 63 */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<4>, reg::reg8_e>(pCpu); },
    /* 64 */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<4>, reg::reg8_h>(pCpu); },
    /* 65 */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<4>, reg::reg8_l>(pCpu); },
    /* 66 */
    [](cpu &pCpu) {
      op::alu_unary_read<alu::op_bit<4>, reg::reg8_indir_hl>(pCpu);
    },
    /* 67 */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<4>, reg::reg8_a>(pCpu); },
    /* 68 */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<5>, reg::reg8_b>(pCpu); },
    /* 69 */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<5>, reg::reg8_c>(pCpu); },
    /* 6a */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<5>, reg::reg8_d>(pCpu); },
    /* 6b */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<5>, reg::reg8_e>(pCpu); },
    /* 6c */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<5>, reg::reg8_h>(pCpu); },
    /* 6d */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<5>, reg::reg8_l>(pCpu); },
    /* 6e */
    [](cpu &pCpu) {
      op::alu_unary_read<alu::op_bit<5>, reg::reg8_indir_hl>(pCpu);
    },
    /* 6f */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<5>, reg::reg8_a>(pCpu); },
    /* 70 */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<6>, reg::reg8_b>(pCpu); },
    /* 71 */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<6>, reg::reg8_c>(pCpu); },
    /* 72 */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<6>, reg::reg8_d>(pCpu); },
    /* 73 */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<6>, reg::reg8_e>(pCpu); },
    /* 74 */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<6>, reg::reg8_h>(pCpu); },
    /* 75 */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<6>, reg::reg8_l>(pCpu); },
    /* 76 */
    [](cpu &pCpu) {
      op::alu_unary_read<alu::op_bit<6>, reg::reg8_indir_hl>(pCpu);
    },
    /* 77 */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<6>, reg::reg8_a>(pCpu); },
    /* 78 */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<7>, reg::reg8_b>(pCpu); },
    /* 79 */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<7>, reg::reg8_c>(pCpu); },
    /* 7a */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<7>, reg::reg8_d>(pCpu); },
    /* 7b */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<7>, reg::reg8_e>(pCpu); },
    /* 7c */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<7>, reg::reg8_h>(pCpu); },
    /* 7d */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<7>, reg::reg8_l>(pCpu); },
    /* 7e */
    [](cpu &pCpu) {
      op::alu_unary_read<alu::op_bit<7>, reg::reg8_indir_hl>(pCpu);
    },
    /* 7f */
    [](cpu &pCpu) { op::alu_unary_read<alu::op_bit<7>, reg::reg8_a>(pCpu); },
    /* 80 */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<0>, reg::reg8_b>(pCpu); },
    /* 81 */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<0>, reg::reg8_c>(pCpu); },
    /* 82 */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<0>, reg::reg8_d>(pCpu); },
    /* 83 */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<0>, reg::reg8_e>(pCpu); },
    /* 84 */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<0>, reg::reg8_h>(pCpu); },
    /* 85 */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<0>, reg::reg8_l>(pCpu); },
    /* 86 */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<0>, reg::reg8_indir_hl>(pCpu); },
    /* 87 */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<0>, reg::reg8_a>(pCpu); },
    /* 88 */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<1>, reg::reg8_b>(pCpu); },
    /* 89 */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<1>, reg::reg8_c>(pCpu); },
    /* 8a */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<1>, reg::reg8_d>(pCpu); },
    /* 8b */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<1>, reg::reg8_e>(pCpu); },
    /* 8c */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<1>, reg::reg8_h>(pCpu); },
    /* 8d */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<1>, reg::reg8_l>(pCpu); },
    /* 8e */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<1>, reg::reg8_indir_hl>(pCpu); },
    /* 8f */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<1>, reg::reg8_a>(pCpu); },
    /* 90 */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<2>, reg::reg8_b>(pCpu); },
    /* 91 */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<2>, reg::reg8_c>(pCpu); },
    /* 92 */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<2>, reg::reg8_d>(pCpu); },
    /* 93 */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<2>, reg::reg8_e>(pCpu); },
    /* 94 */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<2>, reg::reg8_h>(pCpu); },
    /* 95 */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<2>, reg::reg8_l>(pCpu); },
    /* 96 */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<2>, reg::reg8_indir_hl>(pCpu); },
    /* 97 */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<2>, reg::reg8_a>(pCpu); },
    /* 98 */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<3>, reg::reg8_b>(pCpu); },
    /* 99 */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<3>, reg::reg8_c>(pCpu); },
    /* 9a */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<3>, reg::reg8_d>(pCpu); },
    /* 9b */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<3>, reg::reg8_e>(pCpu); },
    /* 9c */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<3>, reg::reg8_h>(pCpu); },
    /* 9d */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<3>, reg::reg8_l>(pCpu); },
    /* 9e */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<3>, reg::reg8_indir_hl>(pCpu); },
    /* 9f */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<3>, reg::reg8_a>(pCpu); },
    /* a0 */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<4>, reg::reg8_b>(pCpu); },
    /* a1 */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<4>, reg::reg8_c>(pCpu); },
    /* a2 */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<4>, reg::reg8_d>(pCpu); },
    /* a3 */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<4>, reg::reg8_e>(pCpu); },
    /* a4 */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<4>, reg::reg8_h>(pCpu); },
    /* a5 */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<4>, reg::reg8_l>(pCpu); },
    /* a6 */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<4>, reg::reg8_indir_hl>(pCpu); },
    /* a7 */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<4>, reg::reg8_a>(pCpu); },
    /* a8 */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<5>, reg::reg8_b>(pCpu); },
    /* a9 */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<5>, reg::reg8_c>(pCpu); },
    /* aa */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<5>, reg::reg8_d>(pCpu); },
    /* ab */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<5>, reg::reg8_e>(pCpu); },
    /* ac */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<5>, reg::reg8_h>(pCpu); },
    /* ad */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<5>, reg::reg8_l>(pCpu); },
    /* ae */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<5>, reg::reg8_indir_hl>(pCpu); },
    /* af */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<5>, reg::reg8_a>(pCpu); },
    /* b0 */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<6>, reg::reg8_b>(pCpu); },
    /* b1 */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<6>, reg::reg8_c>(pCpu); },
    /* b2 */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<6>, reg::reg8_d>(pCpu); },
    /* b3 */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<6>, reg::reg8_e>(pCpu); },
    /* b4 */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<6>, reg::reg8_h>(pCpu); },
    /* b5 */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<6>, reg::reg8_l>(pCpu); },
    /* b6 */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<6>, reg::reg8_indir_hl>(pCpu); },
    /* b7 */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<6>, reg::reg8_a>(pCpu); },
    /* b8 */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<7>, reg::reg8_b>(pCpu); },
    /* b9 */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<7>, reg::reg8_c>(pCpu); },
    /* ba */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<7>, reg::reg8_d>(pCpu); },
    /* bb */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<7>, reg::reg8_e>(pCpu); },
    /* bc */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<7>, reg::reg8_h>(pCpu); },
    /* bd */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<7>, reg::reg8_l>(pCpu); },
    /* be */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<7>, reg::reg8_indir_hl>(pCpu); },
    /* bf */
    [](cpu &pCpu) { op::alu_unary<alu::op_res<7>, reg::reg8_a>(pCpu); },
    /* c0 */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<0>, reg::reg8_b>(pCpu); },
    /* c1 */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<0>, reg::reg8_c>(pCpu); },
    /* c2 */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<0>, reg::reg8_d>(pCpu); },
    /* c3 */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<0>, reg::reg8_e>(pCpu); },
    /* c4 */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<0>, reg::reg8_h>(pCpu); },
    /* c5 */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<0>, reg::reg8_l>(pCpu); },
    /* c6 */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<0>, reg::reg8_indir_hl>(pCpu); },
    /* c7 */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<0>, reg::reg8_a>(pCpu); },
    /* c8 */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<1>, reg::reg8_b>(pCpu); },
    /* c9 */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<1>, reg::reg8_c>(pCpu); },
    /* ca */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<1>, reg::reg8_d>(pCpu); },
    /* cb */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<1>, reg::reg8_e>(pCpu); },
    /* cc */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<1>, reg::reg8_h>(pCpu); },
    /* cd */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<1>, reg::reg8_l>(pCpu); },
    /* ce */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<1>, reg::reg8_indir_hl>(pCpu); },
    /* cf */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<1>, reg::reg8_a>(pCpu); },
    /* d0 */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<2>, reg::reg8_b>(pCpu); },
    /* d1 */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<2>, reg::reg8_c>(pCpu); },
    /* d2 */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<2>, reg::reg8_d>(pCpu); },
    /* d3 */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<2>, reg::reg8_e>(pCpu); },
    /* d4 */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<2>, reg::reg8_h>(pCpu); },
    /* d5 */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<2>, reg::reg8_l>(pCpu); },
    /* d6 */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<2>, reg::reg8_indir_hl>(pCpu); },
    /* d7 */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<2>, reg::reg8_a>(pCpu); },
    /* d8 */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<3>, reg::reg8_b>(pCpu); },
    /* d9 */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<3>, reg::reg8_c>(pCpu); },
    /* da */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<3>, reg::reg8_d>(pCpu); },
    /* db */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<3>, reg::reg8_e>(pCpu); },
    /* dc */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<3>, reg::reg8_h>(pCpu); },
    /* dd */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<3>, reg::reg8_l>(pCpu); },
    /* de */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<3>, reg::reg8_indir_hl>(pCpu); },
    /* df */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<3>, reg::reg8_a>(pCpu); },
    /* e0 */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<4>, reg::reg8_b>(pCpu); },
    /* e1 */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<4>, reg::reg8_c>(pCpu); },
    /* e2 */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<4>, reg::reg8_d>(pCpu); },
    /* e3 */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<4>, reg::reg8_e>(pCpu); },
    /* e4 */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<4>, reg::reg8_h>(pCpu); },
    /* e5 */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<4>, reg::reg8_l>(pCpu); },
    /* e6 */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<4>, reg::reg8_indir_hl>(pCpu); },
    /* e7 */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<4>, reg::reg8_a>(pCpu); },
    /* e8 */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<5>, reg::reg8_b>(pCpu); },
    /* e9 */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<5>, reg::reg8_c>(pCpu); },
    /* ea */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<5>, reg::reg8_d>(pCpu); },
    /* eb */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<5>, reg::reg8_e>(pCpu); },
    /* ec */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<5>, reg::reg8_h>(pCpu); },
    /* ed */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<5>, reg::reg8_l>(pCpu); },
    /* ee */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<5>, reg::reg8_indir_hl>(pCpu); },
    /* ef */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<5>, reg::reg8_a>(pCpu); },
    /* f0 */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<6>, reg::reg8_b>(pCpu); },
    /* f1 */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<6>, reg::reg8_c>(pCpu); },
    /* f2 */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<6>, reg::reg8_d>(pCpu); },
    /* f3 */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<6>, reg::reg8_e>(pCpu); },
    /* f4 */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<6>, reg::reg8_h>(pCpu); },
    /* f5 */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<6>, reg::reg8_l>(pCpu); },
    /* f6 */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<6>, reg::reg8_indir_hl>(pCpu); },
    /* f7 */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<6>, reg::reg8_a>(pCpu); },
    /* f8 */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<7>, reg::reg8_b>(pCpu); },
    /* f9 */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<7>, reg::reg8_c>(pCpu); },
    /* fa */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<7>, reg::reg8_d>(pCpu); },
    /* fb */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<7>, reg::reg8_e>(pCpu); },
    /* fc */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<7>, reg::reg8_h>(pCpu); },
    /* fd */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<7>, reg::reg8_l>(pCpu); },
    /* fe */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<7>, reg::reg8_indir_hl>(pCpu); },
    /* ff */
    [](cpu &pCpu) { op::alu_unary<alu::op_set<7>, reg::reg8_a>(pCpu); },
};
static const std::array<void (*)(cpu &), 256> opcode_main_table = {
    /* 00 */ [](cpu &pCpu) { op::nop(pCpu); },
    /* 01 */ [](cpu &pCpu) { op::ld16_r16_d16<reg::reg16_bc>(pCpu); },
    /* 02 */ [](cpu &pCpu) { op::ld16_r16_a<reg::reg16_bc>(pCpu); },
    /* 03 */ [](cpu &pCpu) { op::inc16<reg::reg16_bc>(pCpu); },
    /* 04 */ [](cpu &pCpu) { op::alu_unary<alu::op_inc, reg::reg8_b>(pCpu); },
    /* 05 */ [](cpu &pCpu) { op::alu_unary<alu::op_dec, reg::reg8_b>(pCpu); },
    /* 06 */ [](cpu &pCpu) { op::ld8_r_d8<reg::reg8_b>(pCpu); },
    /* 07 */ [](cpu &pCpu) { op::alu_unary<alu::op_rlc, reg::reg8_a>(pCpu); },
    /* 08 */ [](cpu &pCpu) { op::ld16_a16_sp(pCpu); },
    /* 09 */ [](cpu &pCpu) { op::add16<reg::reg16_hl, reg::reg16_bc>(pCpu); },
    /* 0a */ [](cpu &pCpu) { op::ld16_a_r16<reg::reg16_bc>(pCpu); },
    /* 0b */ [](cpu &pCpu) { op::dec16<reg::reg16_bc>(pCpu); },
    /* 0c */ [](cpu &pCpu) { op::alu_unary<alu::op_inc, reg::reg8_c>(pCpu); },
    /* 0d */ [](cpu &pCpu) { op::alu_unary<alu::op_dec, reg::reg8_c>(pCpu); },
    /* 0e */ [](cpu &pCpu) { op::ld8_r_d8<reg::reg8_c>(pCpu); },
    /* 0f */ [](cpu &pCpu) { op::alu_unary<alu::op_rrc, reg::reg8_a>(pCpu); },
    /* 10 */ [](cpu &pCpu) { op::stop(pCpu); },
    /* 11 */ [](cpu &pCpu) { op::ld16_r16_d16<reg::reg16_de>(pCpu); },
    /* 12 */ [](cpu &pCpu) { op::ld16_r16_a<reg::reg16_de>(pCpu); },
    /* 13 */ [](cpu &pCpu) { op::inc16<reg::reg16_de>(pCpu); },
    /* 14 */ [](cpu &pCpu) { op::alu_unary<alu::op_inc, reg::reg8_d>(pCpu); },
    /* 15 */ [](cpu &pCpu) { op::alu_unary<alu::op_dec, reg::reg8_d>(pCpu); },
    /* 16 */ [](cpu &pCpu) { op::ld8_r_d8<reg::reg8_d>(pCpu); },
    /* 17 */ [](cpu &pCpu) { op::alu_unary<alu::op_rl, reg::reg8_a>(pCpu); },
    /* 18 */ [](cpu &pCpu) { op::jr_r8(pCpu); },
    /* 19 */ [](cpu &pCpu) { op::add16<reg::reg16_hl, reg::reg16_de>(pCpu); },
    /* 1a */ [](cpu &pCpu) { op::ld16_a_r16<reg::reg16_de>(pCpu); },
    /* 1b */ [](cpu &pCpu) { op::dec16<reg::reg16_de>(pCpu); },
    /* 1c */ [](cpu &pCpu) { op::alu_unary<alu::op_inc, reg::reg8_e>(pCpu); },
    /* 1d */ [](cpu &pCpu) { op::alu_unary<alu::op_dec, reg::reg8_e>(pCpu); },
    /* 1e */ [](cpu &pCpu) { op::ld8_r_d8<reg::reg8_e>(pCpu); },
    /* 1f */ [](cpu &pCpu) { op::alu_unary<alu::op_rr, reg::reg8_a>(pCpu); },
    /* 20 */ [](cpu &pCpu) { op::jr_cond_r8<cond::cond_nz>(pCpu); },
    /* 21 */ [](cpu &pCpu) { op::ld16_r16_d16<reg::reg16_hl>(pCpu); },
    /* 22 */ [](cpu &pCpu) { op::ld16_r16_a<reg::reg16_hl_inc>(pCpu); },
    /* 23 */ [](cpu &pCpu) { op::inc16<reg::reg16_hl>(pCpu); },
    /* 24 */ [](cpu &pCpu) { op::alu_unary<alu::op_inc, reg::reg8_h>(pCpu); },
    /* 25 */ [](cpu &pCpu) { op::alu_unary<alu::op_dec, reg::reg8_h>(pCpu); },
    /* 26 */ [](cpu &pCpu) { op::ld8_r_d8<reg::reg8_h>(pCpu); },
    /* 27 */ [](cpu &pCpu) { op::daa(pCpu); },
    /* 28 */ [](cpu &pCpu) { op::jr_cond_r8<cond::cond_z>(pCpu); },
    /* 29 */ [](cpu &pCpu) { op::add16<reg::reg16_hl, reg::reg16_hl>(pCpu); },
    /* 2a */ [](cpu &pCpu) { op::ld16_a_r16<reg::reg16_hl_inc>(pCpu); },
    /* 2b */ [](cpu &pCpu) { op::dec16<reg::reg16_hl>(pCpu); },
    /* 2c */ [](cpu &pCpu) { op::alu_unary<alu::op_inc, reg::reg8_l>(pCpu); },
    /* 2d */ [](cpu &pCpu) { op::alu_unary<alu::op_dec, reg::reg8_l>(pCpu); },
    /* 2e */ [](cpu &pCpu) { op::ld8_r_d8<reg::reg8_l>(pCpu); },
    /* 2f */ [](cpu &pCpu) { op::cpl(pCpu); },
    /* 30 */ [](cpu &pCpu) { op::jr_cond_r8<cond::cond_nc>(pCpu); },
    /* 31 */ [](cpu &pCpu) { op::ld16_r16_d16<reg::reg16_sp>(pCpu); },
    /* 32 */ [](cpu &pCpu) { op::ld16_r16_a<reg::reg16_hl_dec>(pCpu); },
    /* 33 */ [](cpu &pCpu) { op::inc16<reg::reg16_sp>(pCpu); },
    /* 34 */
    [](cpu &pCpu) { op::alu_unary<alu::op_inc, reg::reg8_indir_hl>(pCpu); },
    /* 35 */
    [](cpu &pCpu) { op::alu_unary<alu::op_dec, reg::reg8_indir_hl>(pCpu); },
    /* 36 */ [](cpu &pCpu) { op::ld8_r_d8<reg::reg8_indir_hl>(pCpu); },
    /* 37 */ [](cpu &pCpu) { op::scf(pCpu); },
    /* 38 */ [](cpu &pCpu) { op::jr_cond_r8<cond::cond_c>(pCpu); },
    /* 39 */ [](cpu &pCpu) { op::add16<reg::reg16_hl, reg::reg16_sp>(pCpu); },
    /* 3a */ [](cpu &pCpu) { op::ld16_a_r16<reg::reg16_hl_dec>(pCpu); },
    /* 3b */ [](cpu &pCpu) { op::dec16<reg::reg16_sp>(pCpu); },
    /* 3c */ [](cpu &pCpu) { op::alu_unary<alu::op_inc, reg::reg8_a>(pCpu); },
    /* 3d */ [](cpu &pCpu) { op::alu_unary<alu::op_dec, reg::reg8_a>(pCpu); },
    /* 3e */ [](cpu &pCpu) { op::ld8_r_d8<reg::reg8_a>(pCpu); },
    /* 3f */ [](cpu &pCpu) { op::ccf(pCpu); },
    /* 40 */ [](cpu &pCpu) { op::ld8<reg::reg8_b, reg::reg8_b>(pCpu); },
    /* 41 */ [](cpu &pCpu) { op::ld8<reg::reg8_b, reg::reg8_c>(pCpu); },
    /* 42 */ [](cpu &pCpu) { op::ld8<reg::reg8_b, reg::reg8_d>(pCpu); },
    /* 43 */ [](cpu &pCpu) { op::ld8<reg::reg8_b, reg::reg8_e>(pCpu); },
    /* 44 */ [](cpu &pCpu) { op::ld8<reg::reg8_b, reg::reg8_h>(pCpu); },
    /* 45 */ [](cpu &pCpu) { op::ld8<reg::reg8_b, reg::reg8_l>(pCpu); },
    /* 46 */ [](cpu &pCpu) { op::ld8<reg::reg8_b, reg::reg8_indir_hl>(pCpu); },
    /* 47 */ [](cpu &pCpu) { op::ld8<reg::reg8_b, reg::reg8_a>(pCpu); },
    /* 48 */ [](cpu &pCpu) { op::ld8<reg::reg8_c, reg::reg8_b>(pCpu); },
    /* 49 */ [](cpu &pCpu) { op::ld8<reg::reg8_c, reg::reg8_c>(pCpu); },
    /* 4a */ [](cpu &pCpu) { op::ld8<reg::reg8_c, reg::reg8_d>(pCpu); },
    /* 4b */ [](cpu &pCpu) { op::ld8<reg::reg8_c, reg::reg8_e>(pCpu); },
    /* 4c */ [](cpu &pCpu) { op::ld8<reg::reg8_c, reg::reg8_h>(pCpu); },
    /* 4d */ [](cpu &pCpu) { op::ld8<reg::reg8_c, reg::reg8_l>(pCpu); },
    /* 4e */ [](cpu &pCpu) { op::ld8<reg::reg8_c, reg::reg8_indir_hl>(pCpu); },
    /* 4f */ [](cpu &pCpu) { op::ld8<reg::reg8_c, reg::reg8_a>(pCpu); },
    /* 50 */ [](cpu &pCpu) { op::ld8<reg::reg8_d, reg::reg8_b>(pCpu); },
    /* 51 */ [](cpu &pCpu) { op::ld8<reg::reg8_d, reg::reg8_c>(pCpu); },
    /* 52 */ [](cpu &pCpu) { op::ld8<reg::reg8_d, reg::reg8_d>(pCpu); },
    /* 53 */ [](cpu &pCpu) { op::ld8<reg::reg8_d, reg::reg8_e>(pCpu); },
    /* 54 */ [](cpu &pCpu) { op::ld8<reg::reg8_d, reg::reg8_h>(pCpu); },
    /* 55 */ [](cpu &pCpu) { op::ld8<reg::reg8_d, reg::reg8_l>(pCpu); },
    /* 56 */ [](cpu &pCpu) { op::ld8<reg::reg8_d, reg::reg8_indir_hl>(pCpu); },
    /* 57 */ [](cpu &pCpu) { op::ld8<reg::reg8_d, reg::reg8_a>(pCpu); },
    /* 58 */ [](cpu &pCpu) { op::ld8<reg::reg8_e, reg::reg8_b>(pCpu); },
    /* 59 */ [](cpu &pCpu) { op::ld8<reg::reg8_e, reg::reg8_c>(pCpu); },
    /* 5a */ [](cpu &pCpu) { op::ld8<reg::reg8_e, reg::reg8_d>(pCpu); },
    /* 5b */ [](cpu &pCpu) { op::ld8<reg::reg8_e, reg::reg8_e>(pCpu); },
    /* 5c */ [](cpu &pCpu) { op::ld8<reg::reg8_e, reg::reg8_h>(pCpu); },
    /* 5d */ [](cpu &pCpu) { op::ld8<reg::reg8_e, reg::reg8_l>(pCpu); },
    /* 5e */ [](cpu &pCpu) { op::ld8<reg::reg8_e, reg::reg8_indir_hl>(pCpu); },
    /* 5f */ [](cpu &pCpu) { op::ld8<reg::reg8_e, reg::reg8_a>(pCpu); },
    /* 60 */ [](cpu &pCpu) { op::ld8<reg::reg8_h, reg::reg8_b>(pCpu); },
    /* 61 */ [](cpu &pCpu) { op::ld8<reg::reg8_h, reg::reg8_c>(pCpu); },
    /* 62 */ [](cpu &pCpu) { op::ld8<reg::reg8_h, reg::reg8_d>(pCpu); },
    /* 63 */ [](cpu &pCpu) { op::ld8<reg::reg8_h, reg::reg8_e>(pCpu); },
    /* 64 */ [](cpu &pCpu) { op::ld8<reg::reg8_h, reg::reg8_h>(pCpu); },
    /* 65 */ [](cpu &pCpu) { op::ld8<reg::reg8_h, reg::reg8_l>(pCpu); },
    /* 66 */ [](cpu &pCpu) { op::ld8<reg::reg8_h, reg::reg8_indir_hl>(pCpu); },
    /* 67 */ [](cpu &pCpu) { op::ld8<reg::reg8_h, reg::reg8_a>(pCpu); },
    /* 68 */ [](cpu &pCpu) { op::ld8<reg::reg8_l, reg::reg8_b>(pCpu); },
    /* 69 */ [](cpu &pCpu) { op::ld8<reg::reg8_l, reg::reg8_c>(pCpu); },
    /* 6a */ [](cpu &pCpu) { op::ld8<reg::reg8_l, reg::reg8_d>(pCpu); },
    /* 6b */ [](cpu &pCpu) { op::ld8<reg::reg8_l, reg::reg8_e>(pCpu); },
    /* 6c */ [](cpu &pCpu) { op::ld8<reg::reg8_l, reg::reg8_h>(pCpu); },
    /* 6d */ [](cpu &pCpu) { op::ld8<reg::reg8_l, reg::reg8_l>(pCpu); },
    /* 6e */ [](cpu &pCpu) { op::ld8<reg::reg8_l, reg::reg8_indir_hl>(pCpu); },
    /* 6f */ [](cpu &pCpu) { op::ld8<reg::reg8_l, reg::reg8_a>(pCpu); },
    /* 70 */ [](cpu &pCpu) { op::ld8<reg::reg8_indir_hl, reg::reg8_b>(pCpu); },
    /* 71 */ [](cpu &pCpu) { op::ld8<reg::reg8_indir_hl, reg::reg8_c>(pCpu); },
    /* 72 */ [](cpu &pCpu) { op::ld8<reg::reg8_indir_hl, reg::reg8_d>(pCpu); },
    /* 73 */ [](cpu &pCpu) { op::ld8<reg::reg8_indir_hl, reg::reg8_e>(pCpu); },
    /* 74 */ [](cpu &pCpu) { op::ld8<reg::reg8_indir_hl, reg::reg8_h>(pCpu); },
    /* 75 */ [](cpu &pCpu) { op::ld8<reg::reg8_indir_hl, reg::reg8_l>(pCpu); },
    /* 76 */ [](cpu &pCpu) { op::halt(pCpu); },
    /* 77 */ [](cpu &pCpu) { op::ld8<reg::reg8_indir_hl, reg::reg8_a>(pCpu); },
    /* 78 */ [](cpu &pCpu) { op::ld8<reg::reg8_a, reg::reg8_b>(pCpu); },
    /* 79 */ [](cpu &pCpu) { op::ld8<reg::reg8_a, reg::reg8_c>(pCpu); },
    /* 7a */ [](cpu &pCpu) { op::ld8<reg::reg8_a, reg::reg8_d>(pCpu); },
    /* 7b */ [](cpu &pCpu) { op::ld8<reg::reg8_a, reg::reg8_e>(pCpu); },
    /* 7c */ [](cpu &pCpu) { op::ld8<reg::reg8_a, reg::reg8_h>(pCpu); },
    /* 7d */ [](cpu &pCpu) { op::ld8<reg::reg8_a, reg::reg8_l>(pCpu); },
    /* 7e */ [](cpu &pCpu) { op::ld8<reg::reg8_a, reg::reg8_indir_hl>(pCpu); },
    /* 7f */ [](cpu &pCpu) { op::ld8<reg::reg8_a, reg::reg8_a>(pCpu); },
    /* 80 */ [](cpu &pCpu) { op::alu_binary<alu::op_add, reg::reg8_b>(pCpu); },
    /* 81 */ [](cpu &pCpu) { op::alu_binary<alu::op_add, reg::reg8_c>(pCpu); },
    /* 82 */ [](cpu &pCpu) { op::alu_binary<alu::op_add, reg::reg8_d>(pCpu); },
    /* 83 */ [](cpu &pCpu) { op::alu_binary<alu::op_add, reg::reg8_e>(pCpu); },
    /* 84 */ [](cpu &pCpu) { op::alu_binary<alu::op_add, reg::reg8_h>(pCpu); },
    /* 85 */ [](cpu &pCpu) { op::alu_binary<alu::op_add, reg::reg8_l>(pCpu); },
    /* 86 */
    [](cpu &pCpu) { op::alu_binary<alu::op_add, reg::reg8_indir_hl>(pCpu); },
    /* 87 */ [](cpu &pCpu) { op::alu_binary<alu::op_add, reg::reg8_a>(pCpu); },
    /* 88 */ [](cpu &pCpu) { op::alu_binary<alu::op_adc, reg::reg8_b>(pCpu); },
    /* 89 */ [](cpu &pCpu) { op::alu_binary<alu::op_adc, reg::reg8_c>(pCpu); },
    /* 8a */ [](cpu &pCpu) { op::alu_binary<alu::op_adc, reg::reg8_d>(pCpu); },
    /* 8b */ [](cpu &pCpu) { op::alu_binary<alu::op_adc, reg::reg8_e>(pCpu); },
    /* 8c */ [](cpu &pCpu) { op::alu_binary<alu::op_adc, reg::reg8_h>(pCpu); },
    /* 8d */ [](cpu &pCpu) { op::alu_binary<alu::op_adc, reg::reg8_l>(pCpu); },
    /* 8e */
    [](cpu &pCpu) { op::alu_binary<alu::op_adc, reg::reg8_indir_hl>(pCpu); },
    /* 8f */ [](cpu &pCpu) { op::alu_binary<alu::op_adc, reg::reg8_a>(pCpu); },
    /* 90 */ [](cpu &pCpu) { op::alu_binary<alu::op_sub, reg::reg8_b>(pCpu); },
    /* 91 */ [](cpu &pCpu) { op::alu_binary<alu::op_sub, reg::reg8_c>(pCpu); },
    /* 92 */ [](cpu &pCpu) { op::alu_binary<alu::op_sub, reg::reg8_d>(pCpu); },
    /* 93 */ [](cpu &pCpu) { op::alu_binary<alu::op_sub, reg::reg8_e>(pCpu); },
    /* 94 */ [](cpu &pCpu) { op::alu_binary<alu::op_sub, reg::reg8_h>(pCpu); },
    /* 95 */ [](cpu &pCpu) { op::alu_binary<alu::op_sub, reg::reg8_l>(pCpu); },
    /* 96 */
    [](cpu &pCpu) { op::alu_binary<alu::op_sub, reg::reg8_indir_hl>(pCpu); },
    /* 97 */ [](cpu &pCpu) { op::alu_binary<alu::op_sub, reg::reg8_a>(pCpu); },
    /* 98 */ [](cpu &pCpu) { op::alu_binary<alu::op_sbc, reg::reg8_b>(pCpu); },
    /* 99 */ [](cpu &pCpu) { op::alu_binary<alu::op_sbc, reg::reg8_c>(pCpu); },
    /* 9a */ [](cpu &pCpu) { op::alu_binary<alu::op_sbc, reg::reg8_d>(pCpu); },
    /* 9b */ [](cpu &pCpu) { op::alu_binary<alu::op_sbc, reg::reg8_e>(pCpu); },
    /* 9c */ [](cpu &pCpu) { op::alu_binary<alu::op_sbc, reg::reg8_h>(pCpu); },
    /* 9d */ [](cpu &pCpu) { op::alu_binary<alu::op_sbc, reg::reg8_l>(pCpu); },
    /* 9e */
    [](cpu &pCpu) { op::alu_binary<alu::op_sbc, reg::reg8_indir_hl>(pCpu); },
    /* 9f */ [](cpu &pCpu) { op::alu_binary<alu::op_sbc, reg::reg8_a>(pCpu); },
    /* a0 */ [](cpu &pCpu) { op::alu_binary<alu::op_and, reg::reg8_b>(pCpu); },
    /* a1 */ [](cpu &pCpu) { op::alu_binary<alu::op_and, reg::reg8_c>(pCpu); },
    /* a2 */ [](cpu &pCpu) { op::alu_binary<alu::op_and, reg::reg8_d>(pCpu); },
    /* a3 */ [](cpu &pCpu) { op::alu_binary<alu::op_and, reg::reg8_e>(pCpu); },
    /* a4 */ [](cpu &pCpu) { op::alu_binary<alu::op_and, reg::reg8_h>(pCpu); },
    /* a5 */ [](cpu &pCpu) { op::alu_binary<alu::op_and, reg::reg8_l>(pCpu); },
    /* a6 */
    [](cpu &pCpu) { op::alu_binary<alu::op_and, reg::reg8_indir_hl>(pCpu); },
    /* a7 */ [](cpu &pCpu) { op::alu_binary<alu::op_and, reg::reg8_a>(pCpu); },
    /* a8 */ [](cpu &pCpu) { op::alu_binary<alu::op_xor, reg::reg8_b>(pCpu); },
    /* a9 */ [](cpu &pCpu) { op::alu_binary<alu::op_xor, reg::reg8_c>(pCpu); },
    /* aa */ [](cpu &pCpu) { op::alu_binary<alu::op_xor, reg::reg8_d>(pCpu); },
    /* ab */ [](cpu &pCpu) { op::alu_binary<alu::op_xor, reg::reg8_e>(pCpu); },
    /* ac */ [](cpu &pCpu) { op::alu_binary<alu::op_xor, reg::reg8_h>(pCpu); },
    /* ad */ [](cpu &pCpu) { op::alu_binary<alu::op_xor, reg::reg8_l>(pCpu); },
    /* ae */
    [](cpu &pCpu) { op::alu_binary<alu::op_xor, reg::reg8_indir_hl>(pCpu); },
    /* af */ [](cpu &pCpu) { op::alu_binary<alu::op_xor, reg::reg8_a>(pCpu); },
    /* b0 */ [](cpu &pCpu) { op::alu_binary<alu::op_or, reg::reg8_b>(pCpu); },
    /* b1 */ [](cpu &pCpu) { op::alu_binary<alu::op_or, reg::reg8_c>(pCpu); },
    /* b2 */ [](cpu &pCpu) { op::alu_binary<alu::op_or, reg::reg8_d>(pCpu); },
    /* b3 */ [](cpu &pCpu) { op::alu_binary<alu::op_or, reg::reg8_e>(pCpu); },
    /* b4 */ [](cpu &pCpu) { op::alu_binary<alu::op_or, reg::reg8_h>(pCpu); },
    /* b5 */ [](cpu &pCpu) { op::alu_binary<alu::op_or, reg::reg8_l>(pCpu); },
    /* b6 */
    [](cpu &pCpu) { op::alu_binary<alu::op_or, reg::reg8_indir_hl>(pCpu); },
    /* b7 */ [](cpu &pCpu) { op::alu_binary<alu::op_or, reg::reg8_a>(pCpu); },
    /* b8 */ [](cpu &pCpu) { op::alu_binary<alu::op_cp, reg::reg8_b>(pCpu); },
    /* b9 */ [](cpu &pCpu) { op::alu_binary<alu::op_cp, reg::reg8_c>(pCpu); },
    /* ba */ [](cpu &pCpu) { op::alu_binary<alu::op_cp, reg::reg8_d>(pCpu); },
    /* bb */ [](cpu &pCpu) { op::alu_binary<alu::op_cp, reg::reg8_e>(pCpu); },
    /* bc */ [](cpu &pCpu) { op::alu_binary<alu::op_cp, reg::reg8_h>(pCpu); },
    /* bd */ [](cpu &pCpu) { op::alu_binary<alu::op_cp, reg::reg8_l>(pCpu); },
    /* be */
    [](cpu &pCpu) { op::alu_binary<alu::op_cp, reg::reg8_indir_hl>(pCpu); },
    /* bf */ [](cpu &pCpu) { op::alu_binary<alu::op_cp, reg::reg8_a>(pCpu); },
    /* c0 */ [](cpu &pCpu) { op::ret_cond<cond::cond_nz>(pCpu); },
    /* c1 */ [](cpu &pCpu) { op::pop16<reg::reg16_bc>(pCpu); },
    /* c2 */ [](cpu &pCpu) { op::jp_cond_a16<cond::cond_nz>(pCpu); },
    /* c3 */ [](cpu &pCpu) { op::jp_a16(pCpu); },
    /* c4 */ [](cpu &pCpu) { op::call_cond_a16<cond::cond_nz>(pCpu); },
    /* c5 */ [](cpu &pCpu) { op::push16<reg::reg16_bc>(pCpu); },
    /* c6 */ [](cpu &pCpu) { op::alu_binary_imm<alu::op_add>(pCpu); },
    /* c7 */ [](cpu &pCpu) { op::rst_nn(pCpu, 0x0); },
    /* c8 */ [](cpu &pCpu) { op::ret_cond<cond::cond_z>(pCpu); },
    /* c9 */ [](cpu &pCpu) { op::ret(pCpu); },
    /* ca */ [](cpu &pCpu) { op::jp_cond_a16<cond::cond_z>(pCpu); },
    /* cb */ [](cpu &pCpu) { exec_op_cb(pCpu); },
    /* cc */ [](cpu &pCpu) { op::call_cond_a16<cond::cond_z>(pCpu); },
    /* cd */ [](cpu &pCpu) { op::call_a16(pCpu); },
    /* ce */ [](cpu &pCpu) { op::alu_binary_imm<alu::op_adc>(pCpu); },
    /* cf */ [](cpu &pCpu) { op::rst_nn(pCpu, 0x8); },
    /* d0 */ [](cpu &pCpu) { op::ret_cond<cond::cond_nc>(pCpu); },
    /* d1 */ [](cpu &pCpu) { op::pop16<reg::reg16_de>(pCpu); },
    /* d2 */ [](cpu &pCpu) { op::jp_cond_a16<cond::cond_nc>(pCpu); },
    /* d3 */ [](cpu &pCpu) { op::nop(pCpu); },
    /* d4 */ [](cpu &pCpu) { op::call_cond_a16<cond::cond_nc>(pCpu); },
    /* d5 */ [](cpu &pCpu) { op::push16<reg::reg16_de>(pCpu); },
    /* d6 */ [](cpu &pCpu) { op::alu_binary_imm<alu::op_sub>(pCpu); },
    /* d7 */ [](cpu &pCpu) { op::rst_nn(pCpu, 0x10); },
    /* d8 */ [](cpu &pCpu) { op::ret_cond<cond::cond_c>(pCpu); },
    /* d9 */ [](cpu &pCpu) { op::reti(pCpu); },
    /* da */ [](cpu &pCpu) { op::jp_cond_a16<cond::cond_c>(pCpu); },
    /* db */ [](cpu &pCpu) { op::nop(pCpu); },
    /* dc */ [](cpu &pCpu) { op::call_cond_a16<cond::cond_c>(pCpu); },
    /* dd */ [](cpu &pCpu) { op::nop(pCpu); },
    /* de */ [](cpu &pCpu) { op::alu_binary_imm<alu::op_sbc>(pCpu); },
    /* df */ [](cpu &pCpu) { op::rst_nn(pCpu, 0x18); },
    /* e0 */ [](cpu &pCpu) { op::ldh8_a8_a(pCpu); },
    /* e1 */ [](cpu &pCpu) { op::pop16<reg::reg16_hl>(pCpu); },
    /* e2 */ [](cpu &pCpu) { op::ld8_c_a(pCpu); },
    /* e3 */ [](cpu &pCpu) { op::nop(pCpu); },
    /* e4 */ [](cpu &pCpu) { op::nop(pCpu); },
    /* e5 */ [](cpu &pCpu) { op::push16<reg::reg16_hl>(pCpu); },
    /* e6 */ [](cpu &pCpu) { op::alu_binary_imm<alu::op_and>(pCpu); },
    /* e7 */ [](cpu &pCpu) { op::rst_nn(pCpu, 0x20); },
    /* e8 */ [](cpu &pCpu) { op::add16_sp_n(pCpu); },
    /* e9 */ [](cpu &pCpu) { op::jp_hl(pCpu); },
    /* ea */ [](cpu &pCpu) { op::ld8_a16_a(pCpu); },
    /* eb */ [](cpu &pCpu) { op::nop(pCpu); },
    /* ec */ [](cpu &pCpu) { op::nop(pCpu); },
    /* ed */ [](cpu &pCpu) { op::nop(pCpu); },
    /* ee */ [](cpu &pCpu) { op::alu_binary_imm<alu::op_xor>(pCpu); },
    /* ef */ [](cpu &pCpu) { op::rst_nn(pCpu, 0x28); },
    /* f0 */ [](cpu &pCpu) { op::ldh8_a_a8(pCpu); },
    /* f1 */ [](cpu &pCpu) { op::pop16<reg::reg16_af>(pCpu); },
    /* f2 */ [](cpu &pCpu) { op::ld8_a_c(pCpu); },
    /* f3 */ [](cpu &pCpu) { op::di(pCpu); },
    /* f4 */ [](cpu &pCpu) { op::nop(pCpu); },
    /* f5 */ [](cpu &pCpu) { op::push16<reg::reg16_af>(pCpu); },
    /* f6 */ [](cpu &pCpu) { op::alu_binary_imm<alu::op_or>(pCpu); },
    /* f7 */ [](cpu &pCpu) { op::rst_nn(pCpu, 0x30); },
    /* f8 */ [](cpu &pCpu) { op::ld16_hl_spr8(pCpu); },
    /* f9 */ [](cpu &pCpu) { op::ld16_sp_hl(pCpu); },
    /* fa */ [](cpu &pCpu) { op::ld8_a_a16(pCpu); },
    /* fb */ [](cpu &pCpu) { op::ei(pCpu); },
    /* fc */ [](cpu &pCpu) { op::nop(pCpu); },
    /* fd */ [](cpu &pCpu) { op::nop(pCpu); },
    /* fe */ [](cpu &pCpu) { op::alu_binary_imm<alu::op_cp>(pCpu); },
    /* ff */ [](cpu &pCpu) { op::rst_nn(pCpu, 0x38); },
};
}; // namespace opcode
}; // namespace cpu

#endif // __OPCODE_TABLE_HPP__
