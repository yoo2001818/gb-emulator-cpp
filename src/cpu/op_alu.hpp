#include <utility>
#include <concepts>
#include "cpu.hpp"
#include "reg.hpp"

#ifndef __OP_ALU_HPP__
#define __OP_ALU_HPP__

using namespace std;

namespace cpu
{
  namespace alu
  {
    class op_binary {
    public:
      static uint8_t exec(cpu &pCpu, const uint8_t pValue1, const uint8_t pValue2) { return 0; };
    };

    class op_add : op_binary {
    public:
      static uint8_t exec(cpu &pCpu, const uint8_t pValue1, const uint8_t pValue2) {
        int result = static_cast<int>(pValue1) + pValue2;
        uint8_t flags = 0;
        if ((result & 0xff) == 0) flags |= reg::FLAG_Z;
        if (((pValue1 & 0xf) + (pValue2 & 0xf)) & 0x10) flags |= reg::FLAG_H;
        if (result & 0x100) flags |= reg::FLAG_C;
        pCpu.mRegister.f = flags;
        return static_cast<uint8_t>(result);
      };
    };

    class op_adc : op_binary {
    public:
      static uint8_t exec(cpu &pCpu, const uint8_t pValue1, const uint8_t pValue2) {
        int result = static_cast<int>(pValue1) + pValue2;
        if (pCpu.mRegister.f & reg::FLAG_C) result += 1;
        uint8_t flags = 0;
        if ((result & 0xff) == 0) flags |= reg::FLAG_Z;
        if (((pValue1 & 0xf) + (pValue2 & 0xf)) & 0x10) flags |= reg::FLAG_H;
        if (result & 0x100) flags |= reg::FLAG_C;
        pCpu.mRegister.f = flags;
        return static_cast<uint8_t>(result);
      };
    };

    class op_sub : op_binary {
    public:
      static uint8_t exec(cpu &pCpu, const uint8_t pValue1, const uint8_t pValue2) {
        int result = static_cast<int>(pValue1) - pValue2;
        uint8_t flags = 0;
        if ((result & 0xff) == 0) flags |= reg::FLAG_Z;
        flags |= reg::FLAG_N;
        if ((pValue1 & 0xf) - (pValue2 & 0xf) < 0) flags |= reg::FLAG_H;
        if (result < 0) flags |= reg::FLAG_C;
        pCpu.mRegister.f = flags;
        return static_cast<uint8_t>(result);
      };
    };

    class op_sbc : op_binary {
    public:
      static uint8_t exec(cpu &pCpu, const uint8_t pValue1, const uint8_t pValue2) {
        int result = static_cast<int>(pValue1) - pValue2;
        if (pCpu.mRegister.f & reg::FLAG_C) result -= 1;
        uint8_t flags = 0;
        if ((result & 0xff) == 0) flags |= reg::FLAG_Z;
        flags |= reg::FLAG_N;
        if ((pValue1 & 0xf) - (pValue2 & 0xf) < 0) flags |= reg::FLAG_H;
        if (result < 0) flags |= reg::FLAG_C;
        pCpu.mRegister.f = flags;
        return static_cast<uint8_t>(result);
      };
    };

    class op_and : op_binary {
    public:
      static uint8_t exec(cpu &pCpu, const uint8_t pValue1, const uint8_t pValue2) {
        uint8_t result = pValue1 & pValue2;
        uint8_t flags = 0;
        if (result == 0) flags |= reg::FLAG_Z;
        flags |= reg::FLAG_H;
        pCpu.mRegister.f = flags;
        return result;
      };
    };

    class op_or : op_binary {
    public:
      static uint8_t exec(cpu &pCpu, const uint8_t pValue1, const uint8_t pValue2) {
        uint8_t result = pValue1 | pValue2;
        uint8_t flags = 0;
        if (result == 0) flags |= reg::FLAG_Z;
        pCpu.mRegister.f = flags;
        return result;
      };
    };

    class op_xor : op_binary {
    public:
      static uint8_t exec(cpu &pCpu, const uint8_t pValue1, const uint8_t pValue2) {
        uint8_t result = pValue1 ^ pValue2;
        uint8_t flags = 0;
        if (result == 0) flags |= reg::FLAG_Z;
        pCpu.mRegister.f = flags;
        return result;
      };
    };

    class op_cp : op_binary {
    public:
      static uint8_t exec(cpu &pCpu, const uint8_t pValue1, const uint8_t pValue2) {
        int result = static_cast<int>(pValue1) - pValue2;
        uint8_t flags = 0;
        if ((result & 0xff) == 0) flags |= reg::FLAG_Z;
        flags |= reg::FLAG_N;
        if ((pValue1 & 0xf) - (pValue2 & 0xf) < 0) flags |= reg::FLAG_H;
        if (result < 0) flags |= reg::FLAG_C;
        pCpu.mRegister.f = flags;
        return pValue1;
      };
    };
  }

  namespace op
  {
    template <typename Op, typename R>
      requires conjunction<is_base_of<alu::op_binary, Op>, is_base_of<reg::reg8, R>>::value
    void alu_binary(cpu &pCpu)
    {
      auto n1 = reg::reg8_a::read(pCpu);
      auto n2 = R::read(pCpu);
      auto result = Op::exec(pCpu, n1, n2);
      reg::reg8_a::write(pCpu, result);
      pCpu.tick(1 + R::clocks);
    }

    template <typename Op>
      requires is_base_of<alu::op_binary, Op>::value
    void alu_binary_imm(cpu &pCpu)
    {
      auto n1 = reg::reg8_a::read(pCpu);
      auto n2 = pCpu.read_next8();
      auto result = Op::exec(pCpu, n1, n2);
      reg::reg8_a::write(pCpu, result);
      pCpu.tick(2);
    }
  }
}

#endif // __OP_ALU_HPP__
