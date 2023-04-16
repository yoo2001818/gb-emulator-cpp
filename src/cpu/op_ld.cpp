#include "op_ld.hpp"

void cpu::op::ld8_a_a16(cpu &pCpu)
{
  uint16_t addr = pCpu.read_next16();
  pCpu.tick(2);
  uint8_t value = pCpu.mMemory.read(addr);
  reg::reg8_a::write(pCpu, value);
  pCpu.tick(2);
}

void cpu::op::ld8_a16_a(cpu &pCpu)
{
  uint16_t addr = pCpu.read_next16();
  pCpu.tick(2);
  uint8_t value = reg::reg8_a::read(pCpu);
  pCpu.mMemory.write(addr, value);
  pCpu.tick(2); 
}

void cpu::op::ld8_a_c(cpu &pCpu)
{
  uint16_t addr = (0xff00 + reg::reg8_c::read(pCpu)) & 0xffff;
  uint8_t value = pCpu.mMemory.read(addr);
  reg::reg8_a::write(pCpu, value);
  pCpu.tick(2);
}

void cpu::op::ld8_c_a(cpu &pCpu)
{
  uint16_t addr = (0xff00 + reg::reg8_c::read(pCpu)) & 0xffff;
  uint8_t value = reg::reg8_a::read(pCpu);
  pCpu.mMemory.write(addr, value);
  pCpu.tick(2);
}

void cpu::op::ldh8_a8_a(cpu &pCpu)
{
  uint16_t addr = (0xff00 + pCpu.read_next8()) & 0xffff;
  pCpu.tick(1);
  uint8_t value = reg::reg8_a::read(pCpu);
  pCpu.mMemory.write(addr, value);
  pCpu.tick(2);
}

void cpu::op::ldh8_a_a8(cpu &pCpu)
{
  uint16_t addr = (0xff00 + pCpu.read_next8()) & 0xffff;
  pCpu.tick(1);
  uint8_t value = pCpu.mMemory.read(addr);
  pCpu.tick(2);
  reg::reg8_a::write(pCpu, value);
}

