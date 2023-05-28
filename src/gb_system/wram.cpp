#include "wram.hpp"
#include "system.hpp"
#include "../memory/lambda_memory.hpp"

static const uint8_t IO_SVBK = 0x70;

void gb_system::wram::register_system()
{
  this->mSystem.mMemoryBus->register_entry(0xc0, 0x20, this->shared_from_this());
  this->mSystem.mMemoryBus->register_entry(0xe0, 0x1e, this->shared_from_this());
  if (this->mSystem.mSystemType == system_type::CGB)
  {
    this->mSystem.mIoBus->register_entry(IO_SVBK, make_shared<::memory::lambda_memory>(
      [&](uint16_t pAddr)
      {
        return this->mBank;
      },
      [&](uint16_t pAddr, uint8_t pValue)
      {
        this->mBank = pValue & 0x7;
        if (this->mBank == 0)
        {
          this->mBank = 1;
        }
      }
    ));
  }
}

void gb_system::wram::reset()
{
  this->mBank = 1;
  this->mBytes.fill(0);
}

uint8_t gb_system::wram::read(uint16_t pAddr)
{
  if (pAddr < 0x1000)
  {
    return this->mBytes[pAddr];
  }
  else
  {
    auto addr = (this->mBank - 1) * 0x1000 + pAddr;
    return this->mBytes[addr];
  }
}

void gb_system::wram::write(uint16_t pAddr, uint8_t pValue)
{
  if (pAddr < 0x1000)
  {
    this->mBytes[pAddr] = pValue;
  }
  else
  {
    auto addr = (this->mBank - 1) * 0x1000 + pAddr;
    this->mBytes[addr] = pValue;
  }
}
