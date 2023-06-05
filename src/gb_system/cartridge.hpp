#include "component.hpp"
#include "../memory/memory.hpp"

#ifndef __CARTRIDGE_HPP__
#define __CARTRIDGE_HPP__

namespace gb_system
{
  class cartridge : public component, public memory::memory
  {
    virtual ~cartridge(){};
    virtual uint8_t read(uint16_t pAddr) = 0;
    virtual void write(uint16_t pAddr, uint8_t pValue) = 0;
    virtual void reset() = 0;
    virtual void register_system() = 0;
    virtual void tick() = 0;
  };
}

#endif // __CARTRIDGE_HPP__
