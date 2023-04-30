#include <cstdint>
#include <utility>
#include <concepts>
#include <array>
#include "cpu.hpp"
#include "reg.hpp"
#include "op_alu.hpp"
#include "op_jmp.hpp"
#include "op_ld.hpp"
#include "op_misc.hpp"

#ifndef __OP_HPP__
#define __OP_HPP__

using namespace std;

namespace cpu
{
  namespace opcode
  {
    using namespace std;
    static const array<void (*)(cpu &), 256> opcode_table = {
      /* 00 */ [](cpu &pCpu) { op::nop(pCpu); },
      /* 01 */ [](cpu &pCpu) { op::ld8<reg::reg8_a, reg::reg8_b>(pCpu); },
      /* 02 */ [](cpu &pCpu) { op::ld8<reg::reg8_b, reg::reg8_c>(pCpu); },
      /* 08 */ [](cpu &pCpu) { op::ld16_a16_sp(pCpu); },
    };
  };
};

#endif // __OP_HPP__
