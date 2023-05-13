#include "../memory/memory.hpp"
#include <cstdint>
#include <array>
#include <memory>

#ifndef __HRAM_HPP__
#define __HRAM_HPP__

using namespace std;

namespace gb_system
{
  class system;
  class hram : public memory::memory, public enable_shared_from_this<hram>
  {
  public:
    hram(system &pSystem) : mSystem(pSystem){};
    void register_system();
    void reset();
    uint8_t read(uint16_t pAddr);
    void write(uint16_t pAddr, uint8_t pValue);
  private:
    system &mSystem;
    array<uint8_t, 0x80> mBytes;
  };
}

#endif // __HRAM_HPP__

