#include <cstdint>

#ifndef __CPU_HPP__
#define __CPU_HPP__

namespace memory
{
  class memory
  {
  public:
    int read(int pAddr);
    void write(int pAddr, int pValue);
  };
};

namespace cpu
{
  class cpu_register
  {
  public:
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    int e = 0;
    int f = 0;
    int h = 0;
    int l = 0;
    int pc = 0;
    int sp = 0;
  };

  class cpu
  {
  public:
    cpu_register mRegister;
    memory::memory mMemory;
    unsigned int mClocks;

    bool mIsRunning = false;
    bool mIsStopped = false;
    bool mIsBlocked = false;
    bool mIsInterruptsEnabled = false;
    bool mIsInterruptsEnabledNext = false;

    cpu(memory::memory pMemory) : mMemory(pMemory)
    {
    }

    void reset()
    {
      this->mRegister = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
      this->mClocks = 0;
      this->mIsStopped = false;
      this->mIsBlocked = false;
      this->mIsInterruptsEnabled = false;
      this->mIsInterruptsEnabledNext = false;
    }

    void jump(int pAddr) {
      this->mRegister.pc = pAddr & 0xffff;
    }

    void step() {
      if (this->mIsBlocked) {
        // Do nothing and pass the time
        this->tick(1);
        return;
      }
      this->mIsInterruptsEnabled = this->mIsInterruptsEnabledNext;
      int pc = this->mRegister.pc;
      int opcode = this->mMemory.read(pc);
      // TODO: Parse opcode
    }

  private:
    void skip(int bytes) {
      this->mRegister.pc = (this->mRegister.pc + bytes) & 0xffff;
    }

    void tick(int pClocks) {
      this->mClocks += pClocks;
      // FIXME: Pass time
    }
  };
};

#endif // __CPU_HPP__
