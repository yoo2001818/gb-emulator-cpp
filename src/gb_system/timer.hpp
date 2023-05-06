#include "component.hpp"

#ifndef __TIMER_HPP__
#define __TIMER_HPP__

namespace gb_system
{
  class system;
  class timer : public component
  {
  private:
    system &mSystem;
    int mClocks;
    int mTima;
    int mTma;
    int mTac;
    bool mTimaDelayed;
    void _post_update_tima();
  public:
    timer(system &pSystem) : mSystem(pSystem){};
    void reset();
    void register_system();
    void tick(int pTicks);
  };
}

#endif // __TIMER_HPP__
