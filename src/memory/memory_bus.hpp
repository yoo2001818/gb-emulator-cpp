#include <array>
#include <memory>
#include "memory.hpp"

#ifndef __MEMORY_BUS_HPP__
#define __MEMORY_BUS_HPP__

using namespace std;

namespace memory
{
  class memory_bus : memory
  {
  private:
    array<shared_ptr<memory>, 256> mEntries;
    array<uint16_t, 256> mOffsets;
  public:
    virtual uint8_t read(uint16_t pAddr);
    virtual void write(uint16_t pAddr, uint8_t pValue);
    virtual void reset();
    void register_entry(int pFrom, int pSize, shared_ptr<memory> pMemory);
    void register_entry(int pFrom, int pSize, shared_ptr<memory> pMemory, int pOffset);
  };
};

#endif // __MEMORY_BUS_HPP__

