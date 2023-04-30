#include <cstdint>
#include <utility>
#include <concepts>
#include <array>
#include "cpu.hpp"
#include "reg.hpp"

#ifndef __OP_MISC_HPP__
#define __OP_MISC_HPP__

using namespace std;

namespace cpu::op
{
  void nop(cpu &pCpu);

  template <typename R>
    requires is_base_of<reg::reg16, R>::value
  void push16(cpu &pCpu)
  {
    pCpu.tick(1);
    uint16_t value = R::read(pCpu);
    pCpu.push16(value);
    pCpu.tick(2);
  }

  template <typename R>
    requires is_base_of<reg::reg16, R>::value
  void pop16(cpu &pCpu)
  {
    uint16_t value = pCpu.pop16();
    pCpu.tick(2);
    R::write(pCpu, value);
  }

  template <typename R1, typename R2>
    requires conjunction<is_base_of<reg::reg16, R1>, is_base_of<reg::reg16, R2>>::value
  void add16(cpu &pCpu)
  {
    int n1 = R1::read(pCpu);
    int n2 = R2::read(pCpu);
    int result = n1 + n2;
    uint8_t flags = pCpu.mRegister.f & reg::FLAG_Z;
    if (((n1 & 0xfff) + (n2 & 0xfff)) & 0x1000) flags |= reg::FLAG_H;
    if (result & 0x10000) flags |= reg::FLAG_C;
    pCpu.mRegister.f = flags;
    R1::write(pCpu, result & 0xffff);
    pCpu.tick(2);
  }

  template <typename R>
    requires is_base_of<reg::reg16, R>::value
  void inc16(cpu &pCpu)
  {
    uint16_t value = R::read(pCpu);
    uint16_t result = value + 1;
    R::write(pCpu, result);
    pCpu.tick(2);
  }

  template <typename R>
    requires is_base_of<reg::reg16, R>::value
  void dec16(cpu &pCpu)
  {
    uint16_t value = R::read(pCpu);
    uint16_t result = value - 1;
    R::write(pCpu, result);
    pCpu.tick(2);
  }
  
  void add16_sp_n(cpu &pCpu);
  void daa(cpu &pCpu);
  void cpl(cpu &pCpu);
  void ccf(cpu &pCpu);
  void scf(cpu &pCpu);
  void halt(cpu &pCpu);
  void stop(cpu &pCpu);
  void di(cpu &pCpu);
  void ei(cpu &pCpu);
};

#endif // __OP_MISC_HPP__
