#include "interrupter.hpp"

using namespace gb_system;

static const uint16_t IE_ADDR = 0xffff;
static const uint16_t IF_ADDR = 0xff0f;

void interrupter::reset()
{
  this->mInterruptsEnable = 0;
  this->mInterruptsFlag = 0;
}

void interrupter::register_system()
{
  // FIXME: Register IE/IF on IO Bus
}

void interrupter::queue_interrupt(int pType)
{
  auto& memory = this->mCpu.mMemory;
  auto ifReg = memory->read(IF_ADDR);
  ifReg |= 1 << pType;
  memory->write(IF_ADDR, ifReg);
}

bool interrupter::is_accepting_interrupt()
{
  auto& memory = this->mCpu.mMemory;
  auto ieReg = memory->read(IE_ADDR);
  return ieReg & 0x1f;
}

void interrupter::step()
{
  if (this->mCpu.mIsInterruptsEnabled || !this->mCpu.mIsRunning) {
    auto& memory = this->mCpu.mMemory;
    // Check interrupts
    auto ifReg = memory->read(IF_ADDR);
    auto ieReg = memory->read(IE_ADDR);
    auto interruptReg = ieReg & ifReg;
    if (interruptReg) {
      // Check which type is generated
      int interruptType = 0;
      while ((interruptReg & 1) == 0) {
        interruptType += 1;
        interruptReg = interruptReg >> 1;
      }
      // Regardless of IME flag, start the CPU (continuing from HALT)
      this->mCpu.mIsRunning = true;
      if (this->mCpu.mIsInterruptsEnabled) {
        // Clear IF register of the type
        memory->write(IF_ADDR, ifReg & ~(1 << interruptType));
        // Generate interrupts
        auto prevPc = this->mCpu.mRegister.pc;
        // Reset IME Flag
        this->mCpu.mIsInterruptsEnabled = false;
        this->mCpu.mIsInterruptsEnabledNext = false;
        // Push PC
        this->mCpu.push16(prevPc);
        this->mCpu.tick(4);
        // Jump to the interrupt handler
        auto addr = 0x40 + (interruptType * 8);
        this->mCpu.jump(addr);
      }
    }
  }
  if (this->mCpu.mIsRunning) {
    this->mCpu.step();
  }
}
