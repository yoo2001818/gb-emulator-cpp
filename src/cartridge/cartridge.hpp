#include <memory>
#include "../gb_system/component.hpp"
#include "../memory/memory.hpp"

#ifndef __CARTRIDGE_HPP__
#define __CARTRIDGE_HPP__

namespace cartridge
{
  class cartridge : public gb_system::component, public memory::memory, public std::enable_shared_from_this<cartridge>
  {
  public:
    virtual ~cartridge(){};
    virtual uint8_t read(uint16_t pAddr) = 0;
    virtual void write(uint16_t pAddr, uint8_t pValue) = 0;
    virtual void reset() = 0;
    virtual void register_system() = 0;
    virtual void tick() = 0;
  };
}

#endif // __CARTRIDGE_HPP__
