#include "cartridge_mbc3.hpp"
#include "../gb_system/system.hpp"

uint8_t cartridge::cartridge_mbc3::read(uint16_t pAddr) {
  if (pAddr < 0x4000) {
    return this->mRom[pAddr % this->mRom.size()];
  } else if (pAddr < 0x8000) {
    return this->mRom[((this->mRomBank * 0x4000) + (pAddr - 0x4000)) %
                      this->mRom.size()];
  } else if (pAddr >= 0xa000 && pAddr < 0xc000) {
    if (!this->mRamEnabled)
      return 0xff;
    if (this->mRamBank < 3) {
      if (this->mRam.size() == 0)
        return 0xff;
      return this->mRam[((this->mRamBank * 0x2000) + (pAddr - 0xa000)) %
                        this->mRam.size()];
    } else {
      // TODO: RTC
      return 0xff;
    }
  }
  return 0;
}

void cartridge::cartridge_mbc3::write(uint16_t pAddr, uint8_t pValue) {
  if (pAddr < 0x2000) {
    // RAM enable
    this->mRamEnabled = (pValue & 0x0A);
  } else if (pAddr < 0x4000) {
    // ROM bank
    this->mRomBank = pValue & 0x7f;
    if (this->mRomBank == 0)
      this->mRomBank = 1;
  } else if (pAddr < 0x6000) {
    // RAM bank
    this->mRamBank = pValue & 0x0f;
    // FIXME: RTC
  } else if (pAddr < 0x8000) {
    // Latch clock data
    // FIXME: RTC
  } else if (pAddr < 0xA000) {
    // Noop
  } else if (pAddr < 0xC000) {
    // RAM
    if (this->mRamEnabled) {
      if (this->mRamBank < 3) {
        if (this->mRam.size() == 0)
          return;
        this->mRam[((this->mRamBank * 0x2000) + (pAddr - 0xa000)) %
                   this->mRam.size()] = pValue;
        this->mRamUpdated = true;
      } else {
        // RTC access
        // FIXME: RTC
      }
    }
  }
}

void cartridge::cartridge_mbc3::reset() {
  this->mRomBank = 1;
  this->mRamBank = 0;
}

void cartridge::cartridge_mbc3::register_system() {
  this->mSystem.mMemoryBus->register_entry(0, 0x80, this->shared_from_this(),
                                           0);
  this->mSystem.mMemoryBus->register_entry(0xa0, 0x20, this->shared_from_this(),
                                           0);
}

void cartridge::cartridge_mbc3::tick() {}
