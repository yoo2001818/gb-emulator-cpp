#include "op_misc.hpp"

void cpu::op::nop(cpu &pCpu) { pCpu.tick(1); }

void cpu::op::add16_sp_n(cpu &pCpu) {
  int n1 = reg::reg16_sp::read(pCpu);
  int n2 = pCpu.read_next8();
  if (n2 & 0x80) {
    n2 = -((~n2 + 1) & 0xff);
  }
  int result = n1 + n2;
  uint8_t flags = 0;
  if (((n1 ^ n2 ^ (result & 0xffff)) & 0x10) == 0x10)
    flags |= reg::FLAG_H;
  if (((n1 ^ n2 ^ (result & 0xffff)) & 0x100) == 0x100)
    flags |= reg::FLAG_C;
  pCpu.mRegister.f = flags;
  reg::reg16_sp::write(pCpu, result);
  pCpu.tick(4);
}

void cpu::op::daa(cpu &pCpu) {
  int value = reg::reg8_a::read(pCpu);
  bool carry = false;
  int correction = 0;
  uint8_t flags = pCpu.mRegister.f;

  if ((flags & reg::FLAG_H) ||
      (!(flags & reg::FLAG_N) && ((value & 0xf) > 9))) {
    correction |= 0x6;
  }
  if ((flags & reg::FLAG_C) || (!(flags & reg::FLAG_N) && (value > 0x99))) {
    correction |= 0x60;
    carry = true;
  }
  value += (flags & reg::FLAG_N) ? -correction : correction;

  flags = flags & reg::FLAG_N;
  if ((value & 0xff) == 0)
    flags |= reg::FLAG_Z;
  if (carry)
    flags |= reg::FLAG_C;
  pCpu.mRegister.f = flags;
  reg::reg8_a::write(pCpu, value);
  pCpu.tick(1);
}

void cpu::op::cpl(cpu &pCpu) {
  uint8_t result = reg::reg8_a::read(pCpu) ^ 0xff;
  reg::reg8_a::write(pCpu, result);
  uint8_t flags = pCpu.mRegister.f & (reg::FLAG_C | reg::FLAG_Z);
  flags |= reg::FLAG_N;
  flags |= reg::FLAG_H;
  pCpu.mRegister.f = flags;
  pCpu.tick(1);
}

void cpu::op::ccf(cpu &pCpu) {
  uint8_t flags = 0;
  flags |= pCpu.mRegister.f & reg::FLAG_Z;
  flags |= (~pCpu.mRegister.f) & reg::FLAG_C;
  pCpu.mRegister.f = flags;
  pCpu.tick(1);
}

void cpu::op::scf(cpu &pCpu) {
  uint8_t flags = 0;
  flags |= pCpu.mRegister.f & reg::FLAG_Z;
  flags |= reg::FLAG_C;
  pCpu.mRegister.f = flags;
  pCpu.tick(1);
}

void cpu::op::halt(cpu &pCpu) {
  pCpu.mIsRunning = false;
  pCpu.tick(1);
}

void cpu::op::stop(cpu &pCpu) {
  pCpu.mIsStopped = true;
  pCpu.mIsRunning = false;
  pCpu.skip(1);
  pCpu.tick(1);
}

void cpu::op::di(cpu &pCpu) {
  pCpu.mIsInterruptsEnabled = false;
  pCpu.mIsInterruptsEnabledNext = false;
  pCpu.tick(1);
}

void cpu::op::ei(cpu &pCpu) {
  pCpu.mIsInterruptsEnabledNext = true;
  pCpu.tick(1);
}
