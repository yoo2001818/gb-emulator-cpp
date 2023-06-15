#include <cstdint>
#include "../cpu/cpu.hpp"

#ifndef __INTERRUPTER_HPP__
#define __INTERRUPTER_HPP__

namespace gb_system
{
  static const int INT_VBLANK = 0;
  static const int INT_LCDC = 1;
  static const int INT_TIMER_OVERFLOW = 2;
  static const int INT_SERIAL_COMPLETE = 3;
  static const int INT_PIN_TRIGGERED = 4;
  class system;
  class interrupter
  {
  private:
    system &mSystem;
    cpu::cpu &mCpu;

  public:
    uint8_t mInterruptsEnable;
    uint8_t mInterruptsFlag;
    interrupter(system &pSystem, cpu::cpu &pCpu) : mSystem(pSystem), mCpu(pCpu){};
    void reset();
    void register_system();
    void queue_interrupt(int pType);
    bool is_accepting_interrupt();
    void step();
  };
}

#endif // __INTERRUPTER_HPP__
