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
    class op_binary
    {
    public:
      static uint8_t exec(cpu &pCpu, const uint8_t pValue1, const uint8_t pValue2) { return 0; };
    };

    class op_add : op_binary
    {
    public:
      static uint8_t exec(cpu &pCpu, const uint8_t pValue1, const uint8_t pValue2)
      {
        int result = static_cast<int>(pValue1) + pValue2;
        uint8_t flags = 0;
        if ((result & 0xff) == 0)
          flags |= reg::FLAG_Z;
        if (((pValue1 & 0xf) + (pValue2 & 0xf)) & 0x10)
          flags |= reg::FLAG_H;
        if (result & 0x100)
          flags |= reg::FLAG_C;
        pCpu.mRegister.f = flags;
        return static_cast<uint8_t>(result);
      };
    };

    class op_adc : op_binary
    {
    public:
      static uint8_t exec(cpu &pCpu, const uint8_t pValue1, const uint8_t pValue2)
      {
        int result = static_cast<int>(pValue1) + pValue2;
        if (pCpu.mRegister.f & reg::FLAG_C)
          result += 1;
        uint8_t flags = 0;
        if ((result & 0xff) == 0)
          flags |= reg::FLAG_Z;
        if (((pValue1 & 0xf) + (pValue2 & 0xf)) & 0x10)
          flags |= reg::FLAG_H;
        if (result & 0x100)
          flags |= reg::FLAG_C;
        pCpu.mRegister.f = flags;
        return static_cast<uint8_t>(result);
      };
    };

    class op_sub : op_binary
    {
    public:
      static uint8_t exec(cpu &pCpu, const uint8_t pValue1, const uint8_t pValue2)
      {
        int result = static_cast<int>(pValue1) - pValue2;
        uint8_t flags = 0;
        if ((result & 0xff) == 0)
          flags |= reg::FLAG_Z;
        flags |= reg::FLAG_N;
        if ((pValue1 & 0xf) - (pValue2 & 0xf) < 0)
          flags |= reg::FLAG_H;
        if (result < 0)
          flags |= reg::FLAG_C;
        pCpu.mRegister.f = flags;
        return static_cast<uint8_t>(result);
      };
    };

    class op_sbc : op_binary
    {
    public:
      static uint8_t exec(cpu &pCpu, const uint8_t pValue1, const uint8_t pValue2)
      {
        int result = static_cast<int>(pValue1) - pValue2;
        if (pCpu.mRegister.f & reg::FLAG_C)
          result -= 1;
        uint8_t flags = 0;
        if ((result & 0xff) == 0)
          flags |= reg::FLAG_Z;
        flags |= reg::FLAG_N;
        if ((pValue1 & 0xf) - (pValue2 & 0xf) < 0)
          flags |= reg::FLAG_H;
        if (result < 0)
          flags |= reg::FLAG_C;
        pCpu.mRegister.f = flags;
        return static_cast<uint8_t>(result);
      };
    };

    class op_and : op_binary
    {
    public:
      static uint8_t exec(cpu &pCpu, const uint8_t pValue1, const uint8_t pValue2)
      {
        uint8_t result = pValue1 & pValue2;
        uint8_t flags = 0;
        if (result == 0)
          flags |= reg::FLAG_Z;
        flags |= reg::FLAG_H;
        pCpu.mRegister.f = flags;
        return result;
      };
    };

    class op_or : op_binary
    {
    public:
      static uint8_t exec(cpu &pCpu, const uint8_t pValue1, const uint8_t pValue2)
      {
        uint8_t result = pValue1 | pValue2;
        uint8_t flags = 0;
        if (result == 0)
          flags |= reg::FLAG_Z;
        pCpu.mRegister.f = flags;
        return result;
      };
    };

    class op_xor : op_binary
    {
    public:
      static uint8_t exec(cpu &pCpu, const uint8_t pValue1, const uint8_t pValue2)
      {
        uint8_t result = pValue1 ^ pValue2;
        uint8_t flags = 0;
        if (result == 0)
          flags |= reg::FLAG_Z;
        pCpu.mRegister.f = flags;
        return result;
      };
    };

    class op_cp : op_binary
    {
    public:
      static uint8_t exec(cpu &pCpu, const uint8_t pValue1, const uint8_t pValue2)
      {
        int result = static_cast<int>(pValue1) - pValue2;
        uint8_t flags = 0;
        if ((result & 0xff) == 0)
          flags |= reg::FLAG_Z;
        flags |= reg::FLAG_N;
        if ((pValue1 & 0xf) - (pValue2 & 0xf) < 0)
          flags |= reg::FLAG_H;
        if (result < 0)
          flags |= reg::FLAG_C;
        pCpu.mRegister.f = flags;
        return pValue1;
      };
    };

    class op_unary
    {
    public:
      static uint8_t exec(cpu &pCpu, const uint8_t pValue) { return 0; };
    };

    class op_inc : op_unary
    {
    public:
      static uint8_t exec(cpu &pCpu, const uint8_t pValue)
      {
        int result = static_cast<int>(pValue) + 1;
        uint8_t flags = 0;
        if (pValue == 0xff) flags |= reg::FLAG_Z;
        if ((pValue & 0xf) == 0xf) flags |= reg::FLAG_H;
        flags |= pCpu.mRegister.f & reg::FLAG_C;
        pCpu.mRegister.f = flags;
        return result & 0xff;
      }
    };

    class op_dec : op_unary
    {
    public:
      static uint8_t exec(cpu &pCpu, const uint8_t pValue)
      {
        int result = static_cast<int>(pValue) - 1;
        uint8_t flags = 0;
        if (pValue == 1) flags |= reg::FLAG_Z;
        flags |= reg::FLAG_N;
        if ((pValue & 0xf) == 0) flags |= reg::FLAG_H;
        flags |= pCpu.mRegister.f & reg::FLAG_C;
        pCpu.mRegister.f = flags;
        return result & 0xff;
      }
    };

    class op_swap : op_unary
    {
    public:
      static uint8_t exec(cpu &pCpu, const uint8_t pValue)
      {
        uint8_t result = ((pValue & 0xf) << 4) | ((pValue >> 4) & 0xf);
        uint8_t flags = 0;
        if (result == 0) flags |= reg::FLAG_Z;
        return result;
      }
    };

    class op_rlc : op_unary
    {
    public:
      static uint8_t exec(cpu &pCpu, const uint8_t pValue)
      {
        uint8_t oldBit = pValue & 0x80;
        uint8_t result = ((pValue << 1) & 0xff) | (oldBit >> 7);
        uint8_t flags = 0;
        if (oldBit) flags |= reg::FLAG_C;
        pCpu.mRegister.f = flags;
        return result;
      }
    };

    class op_rl : op_unary
    {
    public:
      static uint8_t exec(cpu &pCpu, const uint8_t pValue)
      {
        uint8_t oldBit = pValue & 0x80;
        uint8_t result = (pValue << 1) & 0xff;
        if (pCpu.mRegister.f & reg::FLAG_C) {
          result |= 1;
        }
        uint8_t flags = 0;
        if (oldBit) flags |= reg::FLAG_C;
        pCpu.mRegister.f = flags;
        return result;
      }
    };

    class op_rrc : op_unary
    {
    public:
      static uint8_t exec(cpu &pCpu, const uint8_t pValue)
      {
        uint8_t oldBit = pValue & 0x01;
        uint8_t result = ((pValue >> 1) & 0xff) | (oldBit << 7);
        uint8_t flags = 0;
        if (oldBit) flags |= reg::FLAG_C;
        pCpu.mRegister.f = flags;
        return result;
      }
    };

    class op_rr : op_unary
    {
    public:
      static uint8_t exec(cpu &pCpu, const uint8_t pValue)
      {
        uint8_t oldBit = pValue & 0x01;
        uint8_t result = (pValue >> 1) & 0xff;
        if (pCpu.mRegister.f & reg::FLAG_C) {
          result |= 0x80;
        }
        uint8_t flags = 0;
        if (oldBit) flags |= reg::FLAG_C;
        pCpu.mRegister.f = flags;
        return result;
      }
    };

    class op_sla : op_unary
    {
    public:
      static uint8_t exec(cpu &pCpu, const uint8_t pValue)
      {
        uint8_t oldBit = pValue & 0x80;
        uint8_t result = (pValue << 1) & 0xff;
        uint8_t flags = 0;
        if (oldBit) flags |= reg::FLAG_C;
        pCpu.mRegister.f = flags;
        return result;
      }
    };

    class op_sra : op_unary
    {
    public:
      static uint8_t exec(cpu &pCpu, const uint8_t pValue)
      {
        uint8_t oldBit = pValue & 0x01;
        uint8_t result = ((pValue >> 1) & 0xff) | (pValue & 0x80);
        uint8_t flags = 0;
        if (oldBit) flags |= reg::FLAG_C;
        pCpu.mRegister.f = flags;
        return result;
      }
    };

    class op_srl : op_unary
    {
    public:
      static uint8_t exec(cpu &pCpu, const uint8_t pValue)
      {
        uint8_t oldBit = pValue & 0x01;
        uint8_t result = (pValue >> 1) & 0xff;
        uint8_t flags = 0;
        if (oldBit) flags |= reg::FLAG_C;
        pCpu.mRegister.f = flags;
        return result;
      }
    };

    template <int B>
    class op_bit : op_unary
    {
    public:
      static uint8_t exec(cpu &pCpu, const uint8_t pValue)
      {
        auto result = (1 << B) & pValue;
        uint8_t flags = pCpu.mRegister.f & reg::FLAG_C;
        flags |= reg::FLAG_H;
        pCpu.mRegister.f = flags;
        return result;
      }
    };

    template <int B>
    class op_set : op_unary
    {
    public:
      static uint8_t exec(cpu &pCpu, const uint8_t pValue)
      {
        uint8_t result = (1 << B) | pValue;
        return result;
      }
    };

    template <int B>
    class op_res : op_unary
    {
    public:
      static uint8_t exec(cpu &pCpu, const uint8_t pValue)
      {
        uint8_t result = (~(1 << B)) & pValue;
        return result;
      }
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
