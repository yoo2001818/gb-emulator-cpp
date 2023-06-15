#include "component.hpp"

#ifndef __TIMER_HPP__
#define __TIMER_HPP__

namespace gb_system
{
  class system;
  class timer : public component
  {
  public:
    int mClocks;
    int mTima;
    int mTma;
    int mTac;
    bool mTimaDelayed;
    timer(system &pSystem) : mSystem(pSystem){};
    void reset();
    void register_system();
    void tick();

  private:
    system &mSystem;
    void post_update_tima();
  };
}

#endif // __TIMER_HPP__
