#include "component.hpp"
#include <array>
#include <cstdint>

#ifndef __PPU_HPP__
#define __PPU_HPP__

namespace gb_system {
class system;

static const int LCD_WIDTH = 160;
static const int LCD_HEIGHT = 144;

class ppu : public component {
public:
  ppu(system &pSystem) : mSystem(pSystem){};
  void reset();
  void register_system();
  void tick();
  // private:
  system &mSystem;
  uint8_t mLcdc;
  uint8_t mStat;
  uint8_t mScy;
  uint8_t mScx;
  uint8_t mLy;
  uint8_t mLyc;
  uint8_t mBgp;
  uint8_t mObp0;
  uint8_t mObp1;
  uint8_t mWy;
  uint8_t mWx;
  int mLineClock;
  int mClocks;
  int mMode;
  std::array<uint16_t, LCD_WIDTH * LCD_HEIGHT> mFramebuffer;
  std::array<uint8_t, 0x4000> mVram;
  std::array<uint8_t, 0x100> mOam;
  int mVramBank;
  uint8_t mBcps;
  uint8_t mOcps;
  std::array<uint8_t, 64> mBgPalette;
  std::array<uint8_t, 64> mObjPalette;
  void handle_line_change();
  void handle_mode3_enter();
  void handle_mode0_enter();
};
} // namespace gb_system

#endif // __PPU_HPP__
