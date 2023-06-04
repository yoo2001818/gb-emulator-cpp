#include <array>
#include "component.hpp"

#ifndef __GAMEPAD_HPP__
#define __GAMEPAD_HPP__

namespace gb_system
{
  class system;
  class gamepad : public component
  {
  public:
    gamepad(system &pSystem) : mSystem(pSystem){};
    void reset();
    void register_system();
    void tick();

  private:
    system &mSystem;
    std::array<bool, 10> mButtons;
    bool mSelectedNibbleHigh;
  };
}

#endif // __GAMEPAD_HPP_
