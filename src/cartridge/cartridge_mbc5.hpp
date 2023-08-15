#include "cartridge.hpp"
#include <vector>

#ifndef __CARTRIDGE_MBC5_HPP__
#define __CARTRIDGE_MBC5_HPP__

namespace gb_system {
class system;
}
namespace cartridge {
class cartridge_mbc5 : public cartridge {
public:
  cartridge_mbc5(std::vector<uint8_t> pRom, std::vector<uint8_t> pRam,
                 gb_system::system &pSystem)
      : mRom(pRom), mRam(pRam), mSystem(pSystem){};
  uint8_t read(uint16_t pAddr);
  void write(uint16_t pAddr, uint8_t pValue);
  void reset();
  void register_system();
  void tick();

private:
  std::vector<uint8_t> mRom;
  std::vector<uint8_t> mRam;
  gb_system::system &mSystem;
  int mRomBank = 1;
  int mRamBank = 0;
  bool mRamEnabled;
  bool mRamUpdated;
};
} // namespace cartridge

#endif // __CARTRIDGE_MBC5_HPP__
