#include "cartridge_mbc1.hpp"
#include "../gb_system/system.hpp"

uint8_t cartridge::cartridge_mbc1::read(uint16_t pAddr) {
  if (pAddr < 0x4000) {
    // ROM Bank 00
    auto highBank = this->mBankingMode ? (this->mBank & 0x60) : 0;
    return this->mRom[(highBank * 0x4000 + pAddr) % this->mRom.size()];
  } else if (pAddr < 0x8000) {
    // ROM Bank 01..7F
    return this
        ->mRom[(this->mBank * 0x4000 + pAddr - 0x4000) % this->mRom.size()];
  } else if (pAddr < 0xA000) {
    // Noop
    return 0;
  } else if (pAddr < 0xC000) {
    if (this->mRam.size() == 0)
      return 0xff;
    auto highBank = this->mBankingMode ? ((this->mBank >> 4) & 0x3) : 0;
    return this
        ->mRam[(highBank * 0x2000 + (pAddr - 0xA000)) % this->mRam.size()];
  }
  return 0;
}

void cartridge::cartridge_mbc1::write(uint16_t pAddr, uint8_t pValue) {
  if (pAddr < 0x2000) {
    // RAM Enable
    this->mRamEnabled = (pValue & 0x0A);
  } else if (pAddr < 0x4000) {
    // ROM Bank Number
    this->mBank = (this->mBank & ~0x1f) | (pValue & 0x1f);
    if (this->mBank == 0) {
      this->mBank = 1;
    }
  } else if (pAddr < 0x6000) {
    // RAM Bank Number or Upper Bits of ROM Bank Number
    this->mBank = (this->mBank & ~0x60) | ((pValue << 4) & 0x60);
  } else if (pAddr < 0x8000) {
    // Banking Mode Select
    this->mBankingMode = (pValue & 0x01);
  } else if (pAddr < 0xA000) {
    // Noop
  } else if (pAddr < 0xC000) {
    // RAM Bank 00..03
    if (!this->mRamEnabled)
      return;
    if (this->mRam.size() == 0)
      return;
    auto highBank = this->mBankingMode ? ((this->mBank >> 4) & 0x3) : 0;
    this->mRam[(highBank * 0x2000 + (pAddr - 0xA000)) % this->mRam.size()] =
        pValue;
    this->mRamUpdated = true;
  }
}

void cartridge::cartridge_mbc1::reset() {
  this->mBank = 1;
  this->mBankingMode = false;
}

void cartridge::cartridge_mbc1::register_system() {
  this->mSystem.mMemoryBus->register_entry(0, 0x80, this->shared_from_this(),
                                           0);
  this->mSystem.mMemoryBus->register_entry(0xa0, 0x20, this->shared_from_this(),
                                           0);
}

void cartridge::cartridge_mbc1::tick() {}
