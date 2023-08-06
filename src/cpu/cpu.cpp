#include "cpu.hpp"
#include "disasm.hpp"
#include "opcode.hpp"

cpu::cpu::cpu(shared_ptr<memory::memory> pMemory) : mMemory(pMemory){};
void cpu::cpu::reset() {
  this->mRegister = {0x01, 0x13, 0, 0xd8, 0xb0, 0x01, 0x4d, 0, 0x100, 0xfffe};
  this->mClocks = 0;
  this->mIsStopped = false;
  this->mIsBlocked = false;
  this->mIsInterruptsEnabled = false;
  this->mIsInterruptsEnabledNext = false;
  this->mIsRunning = true;
}

void cpu::cpu::step() {
  if (this->mIsBlocked) {
    // Do nothing and pass the time
    this->tick(1);
    return;
  }
  this->mIsInterruptsEnabled = this->mIsInterruptsEnabledNext;
  opcode::exec_op(*this);
}
