#include "../cpu/cpu.hpp"
#include "../memory/memory_bus.hpp"
#include "../memory/io_bus.hpp"
#include "interrupter.hpp"

#ifndef __SYSTEM_HPP__
#define __SYSTEM_HPP__

namespace gb_system
{
  class system
  {
  public:
    shared_ptr<cpu::cpu> mCpu;
    shared_ptr<interrupter> mInterrupter;
    shared_ptr<memory::memory_bus> mMemoryBus;
    shared_ptr<memory::io_bus> mIoBus;

    system();
    void reset();
  };
}

#endif // __SYSTEM_HPP__
