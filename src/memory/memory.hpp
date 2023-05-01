#include <cstdint>

#ifndef __MEMORY_HPP__
#define __MEMORY_HPP__

namespace memory
{
  class memory
  {
  public:
    virtual ~memory() {};
    virtual uint8_t read(uint16_t pAddr) = 0;
    virtual void write(uint16_t pAddr, uint8_t pValue) = 0;
    virtual void reset() = 0;
  };
};

#endif // __MEMORY_HPP__
