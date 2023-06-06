#include "cartridge_raw.hpp"
#include "../gb_system/system.hpp"

uint8_t cartridge::cartridge_raw::read(uint16_t pAddr)
{
  return this->mBytes[pAddr];
}

void cartridge::cartridge_raw::write(uint16_t pAdr, uint8_t pValue)
{
  // We don't allow writing to the cartridge
}

void cartridge::cartridge_raw::reset()
{
}

void cartridge::cartridge_raw::register_system()
{
  this->mSystem.mMemoryBus->register_entry(0, 0x80, this->shared_from_this());
  this->mSystem.mMemoryBus->register_entry(0xa0, 0x20, this->shared_from_this());
}

void cartridge::cartridge_raw::tick()
{
}
