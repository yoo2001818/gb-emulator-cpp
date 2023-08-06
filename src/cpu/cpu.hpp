#include <cstdint>
#include <memory>
#include <functional>
#include "../memory/memory.hpp"

#ifndef __CPU_HPP__
#define __CPU_HPP__

namespace cpu
{
  using namespace std;

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

    void af(const uint16_t &pValue)
    {
      this->a = pValue >> 8;
      this->f = pValue & 0xf0;
    }

    const uint16_t bc() const
    {
      return (this->b << 8) | this->c;
    }

    void bc(const uint16_t &pValue)
    {
      this->b = pValue >> 8;
      this->c = pValue & 0xff;
    }

    const uint16_t de() const
    {
      return (this->d << 8) | this->e;
    }

    void de(const uint16_t &pValue)
    {
      this->d = pValue >> 8;
      this->e = pValue & 0xff;
    }

    const uint16_t hl() const
    {
      return (this->h << 8) | this->l;
    }

    void hl(const uint16_t &pValue)
    {
      this->h = pValue >> 8;
      this->l = pValue & 0xff;
    }
  };

  class cpu
  {
  public:
    cpu_register mRegister;
    shared_ptr<memory::memory> mMemory;
    unsigned int mClocks;
    function<void(int)> mOnTick;

    bool mIsRunning = false;
    bool mIsStopped = false;
    bool mIsBlocked = false;
    bool mIsInterruptsEnabled = false;
    bool mIsInterruptsEnabledNext = false;

    cpu(shared_ptr<memory::memory> pMemory);
    void reset();
    void step();
    void jump(uint16_t pAddr)
    {
      this->mRegister.pc = pAddr;
    }
    void skip(int16_t bytes)
    {
      this->mRegister.pc = this->mRegister.pc + bytes;
    }
    void tick(int pClocks)
    {
      this->mClocks += pClocks;
      if (this->mOnTick)
      {
        this->mOnTick(pClocks);
      }
    }
    void set_on_tick(function<void(int)> pOnTick)
    {
      this->mOnTick = pOnTick;
    }
    uint8_t read_next8()
    {
      uint8_t value = this->mMemory->read(this->mRegister.pc);
      this->skip(1);
      return value;
    }
    int read_nextr8()
    {
      int offset = this->read_next8();
      if (offset & 0x80)
      {
        offset = -((~offset + 1) & 0xff);
      }
      return offset;
    }
    uint16_t read_next16()
    {
      uint16_t value1 = this->mMemory->read(this->mRegister.pc);
      this->tick(1);
      uint16_t value2 = this->mMemory->read(this->mRegister.pc + 1);
      this->skip(2);
      return value1 | (value2 << 8);
    }
    uint8_t readp_next8()
    {
      uint8_t value = this->mMemory->read(this->mRegister.pc);
      this->skip(1);
      return value;
    }
    int readp_nextr8()
    {
      int offset = this->readp_next8();
      if (offset & 0x80)
      {
        offset = -((~offset + 1) & 0xff);
      }
      return offset;
    }
    uint16_t readp_next16()
    {
      uint16_t value1 = this->mMemory->read(this->mRegister.pc);
      this->tick(1);
      uint16_t value2 = this->mMemory->read(this->mRegister.pc + 1);
      return value1 | (value2 << 8);
    }
    void push16(uint16_t value)
    {
      this->mMemory->write(this->mRegister.sp - 1, (value >> 8) & 0xff);
      this->tick(1);
      this->mMemory->write(this->mRegister.sp - 2, value & 0xff);
      this->mRegister.sp = (this->mRegister.sp - 2) & 0xffff;
    }
    uint16_t pop16()
    {
      uint16_t value1 = this->mMemory->read(this->mRegister.sp);
      this->tick(1);
      uint16_t value2 = this->mMemory->read(this->mRegister.sp + 1);
      uint16_t value = value1 | (value2 << 8);
      this->mRegister.sp = (this->mRegister.sp + 2) & 0xffff;
      return value;
    }
  };
};

#endif // __CPU_HPP__
