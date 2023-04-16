#include <cstdint>
#include <utility>
#include <concepts>
#include <array>
#include "cpu.hpp"
#include "reg.hpp"

#ifndef __OP_LD_HPP__
#define __OP_LD_HPP__

using namespace std;

namespace cpu::op
{
  template <typename R1, typename R2>
    requires conjunction<is_base_of<reg::reg8, R1>, is_base_of<reg::reg8, R2>>::value
  void ld8(cpu &pCpu)
  {
    uint8_t value = R2::read(pCpu);
    R1::write(pCpu, value);
    pCpu.skip(1);
    pCpu.tick(R1::clocks + R2::clocks + 1);
  }

  template <typename R>
    requires is_base_of<reg::reg8, R>::value
  void ld8_r_d8(cpu &pCpu)
  {
    if (R::clocks > 0) pCpu.tick(R::clocks);
    uint8_t value = pCpu.read_next8();
    R::write(pCpu, value);
    pCpu::tick(2);
  }

  void ld8_a_a16(cpu &pCpu)
  {
    uint16_t addr = pCpu.read_next16();
    pCpu.tick(2);
    uint8_t value = pCpu.mMemory.read(addr);
    reg::reg8_a::write(pCpu, value);
    pCpu.tick(2); 
  }

  void ld8_a16_a(cpu &pCpu)
  {
    uint16_t addr = pCpu.read_next16();
    pCpu.tick(2);
    uint8_t value = reg::reg8_a::read(pCpu);
    pCpu.mMemory.write(addr, value);
    pCpu.tick(2); 
  }

  void ld8_a_c(cpu &pCpu)
  {
    uint16_t addr = (0xff00 + reg::reg8_c::read(pCpu)) & 0xffff;
    uint8_t value = pCpu.mMemory.read(addr);
    reg::reg8_a::write(pCpu, value);
    pCpu.tick(2);
  }

  void ld8_c_a(cpu &pCpu)
  {
    uint16_t addr = (0xff00 + reg::reg8_c::read(pCpu)) & 0xffff;
    uint8_t value = reg::reg8_a::read(pCpu);
    pCpu.mMemory.write(addr, value);
    pCpu.tick(2);
  }

  template <typename R>
    requires is_base_of<reg::reg16, R>::value
  void ld16_a_r16(cpu &pCpu)
  {
    uint16_t addr = R::read(pCpu);
    uint8_t value = pCpu.mMemory.read(addr);
    reg::reg8_a::write(pCpu, value);
    pCpu::tick(2);
  }

  template <typename R>
    requires is_base_of<reg::reg16, R>::value
  void ld16_r16_a(cpu &pCpu)
  {
    uint16_t addr = R::read(pCpu);
    uint8_t value = reg::reg8_a::read(pCpu);
    pCpu.mMemory.write(addr, value);
    pCpu::tick(2);
  }

  void ldh8_a8_a(cpu &pCpu)
  {
    uint16_t addr = (0xff00 + pCpu.read_next8()) & 0xffff;
    pCpu.tick(1);
    uint8_t value = reg::reg8_a::read(pCpu);
    pCpu.mMemory.write(addr, value);
    pCpu.tick(2);
  }

  void ldh8_a_a8(cpu &pCpu)
  {
    uint16_t addr = (0xff00 + pCpu.read_next8()) & 0xffff;
    pCpu.tick(1);
    uint8_t value = pCpu.mMemory.read(addr);
    pCpu.tick(2);
    reg::reg8_a::write(pCpu, value);
  }

  template <typename R>
    requires is_base_of<reg::reg16, R>::value
  void ld16_r16_d16(cpu &pCpu)
  {
    uint16_t value = pCpu.read_next16();
    R::write(pCpu, value);
    pCpu::tick(3);
  }

  void ld16_a16_sp(cpu &pCpu)
  {
    auto addr = pCpu.read_next16();
    auto value = pCpu.mRegister.sp;
    pCpu.mMemory.write(addr, value & 0xff);
    pCpu.mMemory.write(addr, (value >> 8) & 0xff);
    pCpu.tick(5);
  }

  void ld16_sp_hl(cpu &pCpu)
  {
    uint16_t value = reg::reg16_hl::read(pCpu);
    reg::reg16_sp::write(pCpu, value);
    pCpu.tick(2);
  }

  void ld16_hl_spr8(cpu &pCpu)
  {
    int n1 = reg::reg16_sp::read(pCpu);
    int n2 = pCpu.read_next8();
    if (n2 & 0x80) {
      n2 = -((~n2 + 1) & 0xff);
    }
    uint16_t addr = n1 + n2;
    reg::reg16_hl::write(pCpu, addr);
    uint8_t flags = 0;
    if ((n1 ^ n2 ^ addr) & 0x10) flags |= 0x20;
    if ((n1 ^ n2 ^ addr) & 0x100) flags |= 0x10;
    pCpu.mRegister.f = flags;
    pCpu.tick(3);
  }
};

#endif // __OP_LD_HPP__
