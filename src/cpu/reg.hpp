#include <cstdint>
#include "cpu.hpp"

#ifndef __CPU_REG_HPP__
#define __CPU_REG_HPP__

using namespace std;

namespace cpu
{
  namespace reg
  {
    class reg8
    {
    public:
      static const int clocks = 0;
      static uint8_t read(const cpu &pCpu) { return 0xff; };
      static void write(cpu &pCpu, const uint8_t pValue) {};
    };

    class reg8_a : reg8
    {
    public:
      static const int clocks = 0;
      static uint8_t read(const cpu &pCpu)
      {
        return pCpu.mRegister.a;
      };
      static void write(cpu &pCpu, const uint8_t pValue)
      {
        pCpu.mRegister.a = pValue;
      };
    };

    class reg8_b : reg8
    {
    public:
      static const int clocks = 0;
      static uint8_t read(const cpu &pCpu)
      {
        return pCpu.mRegister.b;
      };
      static void write(cpu &pCpu, const uint8_t pValue)
      {
        pCpu.mRegister.b = pValue;
      };
    };

    class reg8_c : reg8
    {
    public:
      static const int clocks = 0;
      static uint8_t read(const cpu &pCpu)
      {
        return pCpu.mRegister.c;
      };
      static void write(cpu &pCpu, const uint8_t pValue)
      {
        pCpu.mRegister.c = pValue;
      };
    };

    class reg8_d : reg8
    {
    public:
      static const int clocks = 0;
      static uint8_t read(const cpu &pCpu)
      {
        return pCpu.mRegister.d;
      };
      static void write(cpu &pCpu, const uint8_t pValue)
      {
        pCpu.mRegister.d = pValue;
      };
    };

    class reg8_e : reg8
    {
    public:
      static const int clocks = 0;
      static uint8_t read(const cpu &pCpu)
      {
        return pCpu.mRegister.e;
      };
      static void write(cpu &pCpu, const uint8_t pValue)
      {
        pCpu.mRegister.e = pValue;
      };
    };

    class reg8_h : reg8
    {
    public:
      static const int clocks = 0;
      static uint8_t read(const cpu &pCpu)
      {
        return pCpu.mRegister.h;
      };
      static void write(cpu &pCpu, const uint8_t pValue)
      {
        pCpu.mRegister.h = pValue;
      };
    };

    class reg8_l : reg8
    {
    public:
      static const int clocks = 0;
      static uint8_t read(const cpu &pCpu)
      {
        return pCpu.mRegister.l;
      };
      static void write(cpu &pCpu, const uint8_t pValue)
      {
        pCpu.mRegister.l = pValue;
      };
    };

    class reg8_indir_hl : reg8
    {
    public:
      static const int clocks = 1;
      static uint8_t read(cpu &pCpu)
      {
        return pCpu.mMemory.read(pCpu.mRegister.hl());
      };
      static void write(cpu &pCpu, const uint8_t pValue)
      {
        pCpu.mMemory.write(pCpu.mRegister.hl(), pValue);
      };
    };

    class reg16
    {
    public:
      static uint16_t read(cpu &pCpu) { return 0xffff; };
      static void write(cpu &pCpu, const uint16_t pValue) {};
    };

    class reg16_af : reg16
    {
    public:
      static uint16_t read(cpu &pCpu)
      {
        return pCpu.mRegister.af();
      };
      static void write(cpu &pCpu, const uint16_t pValue)
      {
        pCpu.mRegister.af(pValue);
      };
    };

    class reg16_bc : reg16
    {
    public:
      static uint16_t read(cpu &pCpu)
      {
        return pCpu.mRegister.bc();
      };
      static void write(cpu &pCpu, const uint16_t pValue)
      {
        pCpu.mRegister.bc(pValue);
      };
    };

    class reg16_de : reg16
    {
    public:
      static uint16_t read(cpu &pCpu)
      {
        return pCpu.mRegister.de();
      };
      static void write(cpu &pCpu, const uint16_t pValue)
      {
        pCpu.mRegister.de(pValue);
      };
    };

    class reg16_sp : reg16
    {
    public:
      static uint16_t read(cpu &pCpu)
      {
        return pCpu.mRegister.sp;
      };
      static void write(cpu &pCpu, const uint16_t pValue)
      {
        pCpu.mRegister.sp = pValue;
      };
    };

    class reg16_hl : reg16
    {
    public:
      static uint16_t read(cpu &pCpu)
      {
        return pCpu.mRegister.hl();
      };
      static void write(cpu &pCpu, const uint16_t pValue)
      {
        pCpu.mRegister.hl(pValue);
      };
    };

    class reg16_hl_inc : reg16
    {
    public:
      static uint16_t read(cpu &pCpu)
      {
        uint16_t value = pCpu.mRegister.hl();
        pCpu.mRegister.hl(value + 1);
        return value;
      };
      static void write(cpu &pCpu, const uint16_t pValue)
      {
        pCpu.mRegister.hl(pValue);
      };
    };

    class reg16_hl_dec : reg16
    {
    public:
      static uint16_t read(cpu &pCpu)
      {
        uint16_t value = pCpu.mRegister.hl();
        pCpu.mRegister.hl(value - 1);
        return value;
      };
      static void write(cpu &pCpu, const uint16_t pValue)
      {
        pCpu.mRegister.hl(pValue);
      };
    };

    static const uint8_t FLAG_C = 0x10;
    static const uint8_t FLAG_H = 0x20;
    static const uint8_t FLAG_N = 0x40;
    static const uint8_t FLAG_Z = 0x80;
  };
};

#endif // __CPU_REG_HPP__
