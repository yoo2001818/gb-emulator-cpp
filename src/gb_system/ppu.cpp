#include "ppu.hpp"
#include "system.hpp"
#include "../memory/lambda_memory.hpp"
#include "../memory/pointer_memory.hpp"

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
  auto& memoryBus = this->mSystem.mMemoryBus;
  auto& ioBus = this->mSystem.mIoBus;

  // VRAM
  memoryBus->register_entry(0x80, 0x20, make_shared<::memory::lambda_memory>(
    [&](uint16_t pAddr) {
      int offset = this->mVramBank * 0x2000;
      return this->mVram[offset + pAddr];
    },
    [&](uint16_t pAddr, uint8_t pValue) {
      int offset = this->mVramBank * 0x2000;
      this->mVram[offset + pAddr] = pValue;
    }
  ));
  // OAM
  memoryBus->register_entry(0xfe, 1, make_shared<::memory::lambda_memory>(
    [&](uint16_t pAddr) {
      return this->mOam[pAddr];
    },
    [&](uint16_t pAddr, uint8_t pValue) {
      this->mOam[pAddr] = pValue;
    }
  ));

  ioBus->register_entry(IO_LCDC, make_shared<::memory::lambda_memory>(
    [&](uint16_t pAddr) {
      return this->mLcdc;
    },
    [&](uint16_t pAddr, uint8_t pValue) {
      if ((this->mLcdc & 0x80) != (pValue & 0x80)) {
        // LCD stopping / restarting
        this->mLy = 0;
        this->mMode = 0;
        this->mLineClock = 0;
        this->mClocks = 0;
      }
      this->mLcdc = pValue;
    }
  ));
  ioBus->register_entry(IO_STAT, make_shared<::memory::lambda_memory>(
    [&](uint16_t pAddr) {
      uint8_t bits = this->mStat & 0xf8;
      bits |= this->mMode;
      if (this->mLy == this->mLyc) bits |= 4;
      return bits;
    },
    [&](uint16_t pAddr, uint8_t pValue) {
      this->mStat = pValue;
    }
  ));
  ioBus->register_entry(IO_SCY, make_shared<::memory::pointer_memory>(this->mScy));
  ioBus->register_entry(IO_SCX, make_shared<::memory::pointer_memory>(this->mScx));
  ioBus->register_entry(IO_LY, make_shared<::memory::pointer_memory>(this->mLy));
  ioBus->register_entry(IO_LYC, make_shared<::memory::pointer_memory>(this->mLyc));
  ioBus->register_entry(IO_BGP, make_shared<::memory::pointer_memory>(this->mBgp));
  ioBus->register_entry(IO_OBP0, make_shared<::memory::pointer_memory>(this->mObp0));
  ioBus->register_entry(IO_OBP1, make_shared<::memory::pointer_memory>(this->mObp1));
  ioBus->register_entry(IO_WY, make_shared<::memory::pointer_memory>(this->mWy));
  ioBus->register_entry(IO_WX, make_shared<::memory::pointer_memory>(this->mWx));

  // CGB implementation
  if (this->mSystem.mSystemType == system_type::CGB) {
    ioBus->register_entry(IO_VBK, make_shared<::memory::lambda_memory>(
      [&](uint16_t pAddr) {
        return 0xfe | this->mVramBank;
      },
      [&](uint16_t pAddr, uint8_t pValue) {
        this->mVramBank = pValue & 1;
      }
    ));
    ioBus->register_entry(IO_BCPS, make_shared<::memory::pointer_memory>(this->mBcps));
    ioBus->register_entry(IO_BCPD, make_shared<::memory::lambda_memory>(
      [&](uint16_t pAddr) {
        int pos = this->mBcps & 0x3f;
        return this->mBgPalette[pos];
      },
      [&](uint16_t pAddr, uint8_t pValue) {
        int pos = this->mBcps & 0x3f;
        bool autoIncrement = this->mBcps & 0x80;
        if (autoIncrement) {
          this->mBcps = ((pos + 1) & 0x3f) | 0x80;
        }
        this->mBgPalette[pos] = pValue;
      }
    ));
    ioBus->register_entry(IO_OCPS, make_shared<::memory::pointer_memory>(this->mOcps));
    ioBus->register_entry(IO_OCPD, make_shared<::memory::lambda_memory>(
      [&](uint16_t pAddr) {
        int pos = this->mOcps & 0x3f;
        return this->mObjPalette[pos];
      },
      [&](uint16_t pAddr, uint8_t pValue) {
        int pos = this->mOcps & 0x3f;
        bool autoIncrement = this->mOcps & 0x80;
        if (autoIncrement) {
          this->mOcps = ((pos + 1) & 0x3f) | 0x80;
        }
        this->mObjPalette[pos] = pValue;
      }
    ));
  }
}

void gb_system::ppu::tick()
{
  
}
