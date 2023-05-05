#include "../cpu/cpu.hpp"
#include "../memory/memory_bus.hpp"
#include "../memory/io_bus.hpp"
#include "interrupter.hpp"

#ifndef __SYSTEM_HPP__
#define __SYSTEM_HPP__

namespace system
{
  class system
  {
  public:
    cpu::cpu mCpu;
    interrupter mInterrupter;
    memory::memory_bus mMemoryBus;
    memory::io_bus mIoBus;
  };
}

#endif // __SYSTEM_HPP__
