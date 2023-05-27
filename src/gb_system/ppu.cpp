#include "ppu.hpp"
#include "system.hpp"
#include "../memory/lambda_memory.hpp"

static const int IO_LCDC = 0x40;
static const int IO_STAT = 0x41;
static const int IO_SCY = 0x42;
static const int IO_SCX = 0x43;
static const int IO_LY = 0x44;
static const int IO_LYC = 0x45;
static const int IO_BGP = 0x47;
static const int IO_OBP0 = 0x48;
static const int IO_OBP1 = 0x49;
static const int IO_WY = 0x4a;
static const int IO_WX = 0x4b;
static const int IO_VBK = 0x4f;
static const int IO_BCPS = 0x68;
static const int IO_BCPD = 0x69;
static const int IO_OCPS = 0x6a;
static const int IO_OCPD = 0x6b;

void gb_system::ppu::reset()
{
  this->mLcdc = 0x91;
  this->mStat = 0;
  this->mScy = 0;
  this->mScx = 0;
  this->mLy = 0;
  this->mLyc = 0;
  this->mBgp = 0xfc;
  this->mObp0 = 0xff;
  this->mObp1 = 0xff;
  this->mWy = 0;
  this->mWx = 0;
  this->mLineClock = 0;
  this->mClocks = 0;
  this->mMode = 0;
  this->mFramebuffer.fill(0);
  this->mVram.fill(0);
  this->mOam.fill(0);
  this->mVramBank = 0;
  this->mBcps = 0;
  this->mOcps = 0;
  this->mBgPalette.fill(0);
  this->mObjPalette.fill(0);
}

void gb_system::ppu::register_system()
{
  // VRAM
  this->mSystem.mMemoryBus->register_entry(0x80, 0x20, make_shared<::memory::lambda_memory>(
    [&](uint16_t pAddr) {
      return 0;
    },
    [&](uint16_t pAddr, uint8_t pValue) {
    }
  ));
  // OAM
  this->mSystem.mMemoryBus->register_entry(0xfe, 1, make_shared<::memory::lambda_memory>(
    [&](uint16_t pAddr) {
      return 0;
    },
    [&](uint16_t pAddr, uint8_t pValue) {
    }
  ));

  this->mSystem.mIoBus->register_entry(IO_LCDC, 1, make_shared<::memory::lambda_memory>(
    [&](uint16_t pAddr) {
      return 0;
    },
    [&](uint16_t pAddr, uint8_t pValue) {
    }
  ));
  this->mSystem.mIoBus->register_entry(IO_STAT, 1, make_shared<::memory::lambda_memory>(
    [&](uint16_t pAddr) {
      return 0;
    },
    [&](uint16_t pAddr, uint8_t pValue) {
    }
  ));
  // pointer_memory or something like that
}

void gb_system::ppu::tick()
{
  
}
