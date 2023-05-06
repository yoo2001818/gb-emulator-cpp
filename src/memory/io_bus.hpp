#include <array>
#include <memory>
#include "memory.hpp"

#ifndef __IO_BUS_HPP__
#define __IO_BUS_HPP__

using namespace std;

namespace memory
{
  class io_bus : public memory, public enable_shared_from_this<io_bus>
  {
  private:
    array<shared_ptr<memory>, 256> mEntries;
    array<uint16_t, 256> mOffsets;
  public:
    virtual uint8_t read(uint16_t pAddr);
    virtual void write(uint16_t pAddr, uint8_t pValue);
    virtual void reset();
    void register_entry(int pFrom, shared_ptr<memory> pMemory);
    void register_entry(int pFrom, int pSize, shared_ptr<memory> pMemory);
  };
};

#endif // __IO_BUS_HPP__


