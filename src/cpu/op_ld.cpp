#include "op_ld.hpp"

void cpu::op::ld8_a_a16(cpu &pCpu) {
  uint16_t addr = pCpu.read_next16();
  pCpu.tick(1);
  uint8_t value = pCpu.mMemory->read(addr);
  reg::reg8_a::write(pCpu, value);
  pCpu.tick(2);
}

void cpu::op::ld8_a16_a(cpu &pCpu) {
  uint16_t addr = pCpu.read_next16();
  pCpu.tick(1);
  uint8_t value = reg::reg8_a::read(pCpu);
  pCpu.mMemory->write(addr, value);
  pCpu.tick(2);
}

void cpu::op::ld8_a_c(cpu &pCpu) {
  uint16_t addr = (0xff00 + reg::reg8_c::read(pCpu)) & 0xffff;
  uint8_t value = pCpu.mMemory->read(addr);
  reg::reg8_a::write(pCpu, value);
  pCpu.tick(2);
}

void cpu::op::ld8_c_a(cpu &pCpu) {
  uint16_t addr = (0xff00 + reg::reg8_c::read(pCpu)) & 0xffff;
  uint8_t value = reg::reg8_a::read(pCpu);
  pCpu.mMemory->write(addr, value);
  pCpu.tick(2);
}

void cpu::op::ldh8_a8_a(cpu &pCpu) {
  uint16_t addr = (0xff00 + pCpu.read_next8()) & 0xffff;
  pCpu.tick(1);
  uint8_t value = reg::reg8_a::read(pCpu);
  pCpu.mMemory->write(addr, value);
  pCpu.tick(2);
}

void cpu::op::ldh8_a_a8(cpu &pCpu) {
  uint16_t addr = (0xff00 + pCpu.read_next8()) & 0xffff;
  pCpu.tick(1);
  uint8_t value = pCpu.mMemory->read(addr);
  pCpu.tick(2);
  reg::reg8_a::write(pCpu, value);
}

void cpu::op::ld16_a16_sp(cpu &pCpu) {
  auto addr = pCpu.read_next16();
  auto value = pCpu.mRegister.sp;
  pCpu.mMemory->write(addr, value & 0xff);
  pCpu.mMemory->write(addr, (value >> 8) & 0xff);
  pCpu.tick(4);
}

void cpu::op::ld16_sp_hl(cpu &pCpu) {
  uint16_t value = reg::reg16_hl::read(pCpu);
  reg::reg16_sp::write(pCpu, value);
  pCpu.tick(2);
}

void cpu::op::ld16_hl_spr8(cpu &pCpu) {
  int n1 = reg::reg16_sp::read(pCpu);
  int n2 = pCpu.read_next8();
  if (n2 & 0x80) {
    n2 = -((~n2 + 1) & 0xff);
  }
  uint16_t addr = n1 + n2;
  reg::reg16_hl::write(pCpu, addr);
  uint8_t flags = 0;
  if ((n1 ^ n2 ^ addr) & 0x10)
    flags |= reg::FLAG_H;
  if ((n1 ^ n2 ^ addr) & 0x100)
    flags |= reg::FLAG_C;
  pCpu.mRegister.f = flags;
  pCpu.tick(3);
}
