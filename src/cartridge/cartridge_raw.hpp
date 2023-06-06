#include "cartridge.hpp"
#include <vector>

#ifndef __CARTRIDGE_RAW_HPP__
#define __CARTRIDGE_RAW_HPP__

namespace gb_system
{
  class system;
}
namespace cartridge
{
  class cartridge_raw : public cartridge
  {
  public:
    cartridge_raw(std::vector<uint8_t> pBytes, gb_system::system &pSystem) : mBytes(pBytes), mSystem(pSystem){};
    uint8_t read(uint16_t pAddr);
    void write(uint16_t pAddr, uint8_t pValue);
    void reset();
    void register_system();
    void tick();

  private:
    std::vector<uint8_t> mBytes;
    gb_system::system &mSystem;
  };
}

#endif // __CARTRIDGE_HPP__
