#include "cpu.hpp"
#include "disasm.hpp"
#include "opcode.hpp"
#include <format>

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
  auto pc = this->mRegister.pc;
  if (this->mIsBreakpointsEnabled) {
    auto matches =
        std::any_of(this->mBreakpoints.begin(), this->mBreakpoints.end(),
                    [pc](const breakpoint &v) {
                      return v.type == breakpoint::READ && v.addr == pc;
                    });
    if (matches) {
      this->mIsTrapped = true;
      return;
    }
  }
  this->mIsInterruptsEnabled = this->mIsInterruptsEnabledNext;
  opcode::exec_op(*this);
}

std::string cpu::cpu::debug_state() {
  return std::format(
      "AF: {:04x} BC: {:04x} DE: {:04x} HL: {:04x} SP: {:04x} PC: {:04x}",
      this->mRegister.af(), this->mRegister.bc(), this->mRegister.de(),
      this->mRegister.hl(), this->mRegister.sp, this->mRegister.pc);
}
