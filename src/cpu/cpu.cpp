#include "cpu.hpp"
#include "opcode.hpp"

cpu::cpu::cpu(shared_ptr<memory::memory> pMemory) : mMemory(pMemory) {};
void cpu::cpu::reset()
{
  this->mRegister = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  this->mClocks = 0;
  this->mIsStopped = false;
  this->mIsBlocked = false;
  this->mIsInterruptsEnabled = false;
  this->mIsInterruptsEnabledNext = false;
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
