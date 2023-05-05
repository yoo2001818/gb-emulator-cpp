#include <cstdint>
#include "../cpu/cpu.hpp"

#ifndef __INTERRUPTER_HPP__
#define __INTERRUPTER_HPP__

namespace system {
  class system;
  class interrupter {
  private:
    system& mSystem;
    cpu::cpu& mCpu;
    uint8_t mInterruptsEnable;
    uint8_t mInterruptsFlag;
  public:
    interrupter(system& pSystem, cpu::cpu& pCpu) : mSystem(pSystem), mCpu(pCpu) {};
    void reset();
    void register_system();
    void queue_interrupt(int pType);
    bool is_accepting_interrupt();
    void step();
  };
}

#endif // __INTERRUPTER_HPP__
