#include <cstdint>
#include <utility>
#include <concepts>
#include "cpu.hpp"

#ifndef __OP_HPP__
#define __OP_HPP__

using namespace std;

namespace cpu
{
  namespace reg
  {
    class reg8
    {
    public:
      static const int clocks = 0;
      static uint8_t read(const cpu& pCpu) { return 0xff; };
      static void write(const cpu& pCpu, const uint8_t pValue) {};
    };

    class reg8_a : reg8
    {
    public:
      static const int clocks = 0;
      static uint8_t read(const cpu& pCpu)
      {
        return pCpu.mRegister.a;
      };
      static void write(cpu& pCpu, const uint8_t pValue)
      {
        pCpu.mRegister.a = pValue;
      };
    };

    class reg8_b : reg8
    {
    public:
      static const int clocks = 0;
      static uint8_t read(const cpu& pCpu)
      {
        return pCpu.mRegister.b;
      };
      static void write(cpu& pCpu, const uint8_t pValue)
      {
        pCpu.mRegister.b = pValue;
      };
    };

    class reg8_c : reg8
    {
    public:
      static const int clocks = 0;
      static uint8_t read(const cpu& pCpu)
      {
        return pCpu.mRegister.c;
      };
      static void write(cpu& pCpu, const uint8_t pValue)
      {
        pCpu.mRegister.c = pValue;
      };
    };

    class reg8_d : reg8
    {
    public:
      static const int clocks = 0;
      static uint8_t read(const cpu& pCpu)
      {
        return pCpu.mRegister.d;
      };
      static void write(cpu& pCpu, const uint8_t pValue)
      {
        pCpu.mRegister.d = pValue;
      };
    };

    class reg8_e : reg8
    {
    public:
      static const int clocks = 0;
      static uint8_t read(const cpu& pCpu)
      {
        return pCpu.mRegister.e;
      };
      static void write(cpu& pCpu, const uint8_t pValue)
      {
        pCpu.mRegister.e = pValue;
      };
    };
  
    class reg8_h : reg8
    {
    public:
      static const int clocks = 0;
      static uint8_t read(const cpu& pCpu)
      {
        return pCpu.mRegister.h;
      };
      static void write(cpu& pCpu, const uint8_t pValue)
      {
        pCpu.mRegister.h = pValue;
      };
    };

    class reg8_l : reg8
    {
    public:
      static const int clocks = 0;
      static uint8_t read(const cpu& pCpu)
      {
        return pCpu.mRegister.l;
      };
      static void write(cpu& pCpu, const uint8_t pValue)
      {
        pCpu.mRegister.l = pValue;
      };
    };
  
    class reg8_indir_hl : reg8
    {
    public:
      static const int clocks = 1;
      static uint8_t read(cpu& pCpu)
      {
        return pCpu.mMemory.read(pCpu.mRegister.hl());
      };
      static void write(cpu& pCpu, const uint8_t pValue)
      {
        pCpu.mMemory.write(pCpu.mRegister.hl(), pValue);
      };
    };
  };
  namespace op 
  {
    template<typename R1, typename R2>
    requires std::conjunction<std::is_base_of<reg::reg8, R1>, std::is_base_of<reg::reg8, R2>>::value
    void ld8(cpu& pCpu) {
      uint8_t value = R2::read(pCpu);
      R1::write(pCpu, value);
      pCpu.skip(1);
      pCpu.tick(R1::clocks + R2::clocks + 1);
    }
  };
};

#endif // __OP_HPP__
