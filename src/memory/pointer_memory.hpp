#include <functional>
#include "memory.hpp"

#ifndef __POINTER_MEMORY_HPP__
#define __POINTER_MEMORY_HPP__

using namespace std;

namespace memory
{
  class pointer_memory : public memory
  {
  public:
    uint8_t &mValue;
    pointer_memory(uint8_t &pValue) : mValue(pValue) {}
    virtual uint8_t read(uint16_t pAddr);
    virtual void write(uint16_t pAddr, uint8_t pValue);
    virtual void reset();
  };
};

#endif // __POINTER_MEMORY_HPP__

