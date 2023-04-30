#include "cpu.hpp"
#include "opcode.hpp"

cpu::cpu::cpu(memory::memory pMemory) : mMemory(pMemory) {};
void cpu::cpu::reset()
{
  this->mRegister = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  this->mClocks = 0;
  this->mIsStopped = false;
  this->mIsBlocked = false;
  this->mIsInterruptsEnabled = false;
  this->mIsInterruptsEnabledNext = false;
}

void cpu::cpu::jump(uint16_t pAddr)
{
  this->mRegister.pc = pAddr;
}

void cpu::cpu::step()
{
  if (this->mIsBlocked) {
    // Do nothing and pass the time
    this->tick(1);
    return;
  }
  this->mIsInterruptsEnabled = this->mIsInterruptsEnabledNext;
  opcode::exec_op(*this);
}

void cpu::cpu::skip(int16_t bytes)
{
  this->mRegister.pc = this->mRegister.pc + bytes;
}

void cpu::cpu::tick(int pClocks)
{
  this->mClocks += pClocks;
  // FIXME: Pass time
}

uint8_t cpu::cpu::read_next8()
{
  uint8_t value = this->mMemory.read(this->mRegister.pc);
  this->skip(1);
  return value;
}

uint16_t cpu::cpu::read_next16()
{
  uint16_t value1 = this->mMemory.read(this->mRegister.pc);
  this->tick(1);
  uint16_t value2 = this->mMemory.read(this->mRegister.pc + 1);
  this->skip(2);
  return value1 | (value2 << 8);
}

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
