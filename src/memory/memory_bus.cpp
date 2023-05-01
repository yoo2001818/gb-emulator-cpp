#include "memory_bus.hpp"

uint8_t memory::memory_bus::read(uint16_t pAddr)
{
  auto id = pAddr >> 8;
  auto port = this->mEntries[id];
  auto offset = this->mOffsets[id];
  if (port == nullptr) return 0xff;
  return port->read(pAddr - offset);
}

void memory::memory_bus::write(uint16_t pAddr, uint8_t pValue)
{
  auto id = pAddr >> 8;
  auto port = this->mEntries[id];
  auto offset = this->mOffsets[id];
  if (port == nullptr) return;
  return port->write(pAddr - offset, pValue);
}

void memory::memory_bus::reset()
{
  this->mEntries.fill(nullptr);
  this->mOffsets.fill(0);
}

void memory::memory_bus::register_entry(int pFrom, int pSize, shared_ptr<memory> pMemory)
{
  this->register_entry(pFrom, pSize, pMemory, pFrom << 8);
}

void memory::memory_bus::register_entry(int pFrom, int pSize, shared_ptr<memory> pMemory, int pOffset)
{
  for (int i = 0; i < pSize; i += 1)
  {
    this->mEntries[pFrom + i] = pMemory;
    this->mOffsets[pFrom + i] = pOffset;
  }
}
