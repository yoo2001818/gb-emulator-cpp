#include "../cpu/cpu.hpp"
#include "../memory/memory_bus.hpp"
#include "../memory/io_bus.hpp"
#include "interrupter.hpp"
#include "timer.hpp"
#include "wram.hpp"
#include "hram.hpp"
#include "ppu.hpp"
#include "gamepad.hpp"

#ifndef __SYSTEM_HPP__
#define __SYSTEM_HPP__

namespace gb_system
{
  enum system_type
  {
    DMG,
    CGB,
    SGB
  };
  class system
  {
  public:
    shared_ptr<cpu::cpu> mCpu;
    shared_ptr<interrupter> mInterrupter;
    shared_ptr<memory::memory_bus> mMemoryBus;
    shared_ptr<memory::io_bus> mIoBus;
    shared_ptr<timer> mTimer;
    shared_ptr<wram> mWram;
    shared_ptr<hram> mHram;
    shared_ptr<ppu> mPpu;
    shared_ptr<gamepad> mGamepad;
    system_type mSystemType;

    system(system_type pSystemType);
    void reset();
    void tick(int pTicks);
  };
}

#endif // __SYSTEM_HPP__
