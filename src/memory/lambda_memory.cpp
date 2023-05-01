#include "lambda_memory.hpp"

uint8_t memory::lambda_memory::read(uint16_t pAddr)
{
  return this->mReadFn(pAddr);
}

void memory::lambda_memory::write(uint16_t pAddr, uint8_t pValue)
{
  this->mWriteFn(pAddr, pValue);
}

void memory::lambda_memory::reset()
{
}
