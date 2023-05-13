#include "hram.hpp"
#include "system.hpp"

void gb_system::hram::register_system()
{
  this->mSystem.mIoBus->register_entry(0x80, 0x7f, this->shared_from_this());
}

void gb_system::hram::reset()
{
  this->mBytes.fill(0);
}

uint8_t gb_system::hram::read(uint16_t pAddr)
{
  return this->mBytes[pAddr];
}

void gb_system::hram::write(uint16_t pAddr, uint8_t pValue)
{
  this->mBytes[pAddr] = pValue;
}

