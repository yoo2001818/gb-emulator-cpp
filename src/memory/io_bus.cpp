#include "io_bus.hpp"

uint8_t memory::io_bus::read(uint16_t pAddr)
{
  auto port = this->mEntries[pAddr];
  auto offset = this->mOffsets[pAddr];
  if (port == nullptr) return 0xff;
  return port->read(pAddr - offset);
}

void memory::io_bus::write(uint16_t pAddr, uint8_t pValue)
{
  auto port = this->mEntries[pAddr];
  auto offset = this->mOffsets[pAddr];
  if (port == nullptr) return;
  return port->write(pAddr - offset, pValue);
}

void memory::io_bus::reset()
{
  this->mEntries.fill(nullptr);
  this->mOffsets.fill(0);
}

void memory::io_bus::register_entry(int pFrom, int pSize, shared_ptr<memory> pMemory)
{
  for (int i = 0; i < pSize; i += 1)
  {
    this->mEntries[pFrom + i] = pMemory;
    this->mOffsets[pFrom + i] = pFrom;
  }
}

void memory::io_bus::register_entry(int pFrom, shared_ptr<memory> pMemory)
{
  this->register_entry(pFrom, 1, pMemory);
}

