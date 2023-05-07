#include "../memory/memory.hpp"
#include <cstdint>
#include <array>

#ifndef __WRAM_HPP__
#define __WRAM_HPP__

using namespace std;

namespace gb_system
{
  class system;
  class wram : public memory::memory, public enable_shared_from_this<wram>
  {
  public:
    wram(system &pSystem) : mSystem(pSystem){};
    void register_system();
    void reset();
    uint8_t read(uint16_t pAddr);
    void write(uint16_t pAddr, uint8_t pValue);
  private:
    system &mSystem;
    uint8_t mBank;
    array<uint8_t, 0x8000> mBytes;
  };
}

#endif // __WRAM_HPP__
