#include "pointer_memory.hpp"

uint8_t memory::pointer_memory::read(uint16_t pAddr)
{
  return this->mValue;
}

void memory::pointer_memory::write(uint16_t pAddr, uint8_t pValue)
{
  this->mValue = pValue;
}

void memory::pointer_memory::reset()
{
}

