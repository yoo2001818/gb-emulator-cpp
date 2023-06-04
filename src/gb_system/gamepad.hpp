#include <array>
#include "component.hpp"

#ifndef __GAMEPAD_HPP__
#define __GAMEPAD_HPP__

namespace gb_system
{
  enum gamepad_button
  {
    RIGHT = 0,
    LEFT = 1,
    UP = 2,
    DOWN = 3,
    A = 4,
    B = 5,
    SELECT = 6,
    START = 7
  };
  class system;
  class gamepad : public component
  {
  public:
    gamepad(system &pSystem) : mSystem(pSystem){};
    void reset();
    void register_system();
    void tick();
    void set(int pButtonId, bool pState);

  private:
    system &mSystem;
    std::array<bool, 8> mButtons;
    bool mSelectedNibbleHigh;
  };
}

#endif // __GAMEPAD_HPP_
