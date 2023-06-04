#include "gamepad.hpp"
#include "system.hpp"
#include "../memory/lambda_memory.hpp"

static const int IO_JOYP = 0x00;

void gb_system::gamepad::reset()
{
  this->mSelectedNibbleHigh = false;
  this->mButtons.fill(false);
}

void gb_system::gamepad::register_system()
{
  this->mSystem.mIoBus->register_entry(IO_JOYP, make_shared<memory::lambda_memory>(
                                                    [&](uint16_t pAddr)
                                                    {
                                                      uint8_t output = 0;
                                                      int offset = this->mSelectedNibbleHigh ? 4 : 0;
                                                      if (!this->mButtons[offset + 0])
                                                        output |= 0x1;
                                                      if (!this->mButtons[offset + 1])
                                                        output |= 0x2;
                                                      if (!this->mButtons[offset + 2])
                                                        output |= 0x4;
                                                      if (!this->mButtons[offset + 3])
                                                        output |= 0x8;
                                                      return output;
                                                    },
                                                    [&](uint16_t pAddr, uint8_t pValue)
                                                    {
                                                      if (pValue & 0x20)
                                                      {
                                                        this->mSelectedNibbleHigh = true;
                                                      }
                                                      else if (pValue & 0x10)
                                                      {
                                                        this->mSelectedNibbleHigh = false;
                                                      }
                                                    }));
}

void gb_system::gamepad::tick()
{
  // noop
}

void gb_system::gamepad::set(int pButtonId, bool pState)
{
  if (pState)
  {
    this->mSystem.mInterrupter->queue_interrupt(INT_PIN_TRIGGERED);
  }
  this->mButtons[pButtonId] = pState;
}
