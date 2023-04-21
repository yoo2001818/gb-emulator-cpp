#include "cpu.hpp"

void cpu::cpu::push16(uint16_t value)
{
  this->mMemory.write(this->mRegister.sp - 1, (value >> 8) & 0xff);
  this->tick(1);
  this->mMemory.write(this->mRegister.sp - 2, value & 0xff);
  this->mRegister.sp = (this->mRegister.sp - 2) & 0xffff;
}

uint16_t cpu::cpu::pop16()
{
  uint16_t value1 = this->mMemory.read(this->mRegister.sp);
  this->tick(1);
  uint16_t value2 = this->mMemory.read(this->mRegister.sp + 1);
  uint16_t value = value1 | (value2 << 8);
  this->mRegister.sp = (this->mRegister.sp + 2) & 0xffff;
  return value;
}
