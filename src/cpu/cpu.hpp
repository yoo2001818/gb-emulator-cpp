#include <cstdint>

#ifndef __CPU_HPP__
#define __CPU_HPP__

namespace memory
{
  class memory
  {
  public:
    int read(int pAddr) { return 0xff; };
    void write(int pAddr, int pValue) {};
  };
};

namespace cpu
{
  class cpu_register
  {
  public:
    uint8_t a = 0;
    uint8_t b = 0;
    uint8_t c = 0;
    uint8_t d = 0;
    uint8_t e = 0;
    uint8_t f = 0;
    uint8_t h = 0;
    uint8_t l = 0;
    uint16_t pc = 0;
    uint16_t sp = 0;

    const uint16_t af() const
    {
      return (this->a << 8) | this->f;
    }

    void af(const uint16_t& pValue)
    {
      this->a = pValue >> 8;
      this->f = pValue & 0xf0;
    }

    const uint16_t bc() const
    {
      return (this->b << 8) | this->c;
    }

    void bc(const uint16_t& pValue)
    {
      this->b = pValue >> 8;
      this->c = pValue & 0xff;
    }

    const uint16_t de() const
    {
      return (this->d << 8) | this->e;
    }

    void de(const uint16_t& pValue)
    {
      this->d = pValue >> 8;
      this->e = pValue & 0xff;
    }

    const uint16_t hl() const
    {
      return (this->h << 8) | this->l;
    }

    void hl(const uint16_t& pValue)
    {
      this->h = pValue >> 8;
      this->l = pValue & 0xff;
    }
    
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

    void jump(uint16_t pAddr) {
      this->mRegister.pc = pAddr;
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
    void skip(int16_t bytes) {
      this->mRegister.pc = this->mRegister.pc + bytes;
    }

    void tick(int pClocks) {
      this->mClocks += pClocks;
      // FIXME: Pass time
    }
  };
};

#endif // __CPU_HPP__
