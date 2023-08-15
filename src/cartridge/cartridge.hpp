#include "../gb_system/component.hpp"
#include "../memory/memory.hpp"
#include <memory>
#include <string>
#include <vector>

#ifndef __CARTRIDGE_HPP__
#define __CARTRIDGE_HPP__

namespace gb_system {
class system;
}
namespace cartridge {
class cartridge : public gb_system::component,
                  public memory::memory,
                  public std::enable_shared_from_this<cartridge> {
public:
  virtual ~cartridge(){};
  virtual uint8_t read(uint16_t pAddr) = 0;
  virtual void write(uint16_t pAddr, uint8_t pValue) = 0;
  virtual void reset() = 0;
  virtual void register_system() = 0;
  virtual void tick() = 0;
};
class cartridge_info {
public:
  std::string title;
  bool supportsCGB;
  bool requiresCGB;
  bool supportsSGB;
  int mbcType;
  int romSize;
  int ramSize;

  cartridge_info(std::vector<uint8_t> pRom);
  // TODO: RAM support
  std::shared_ptr<cartridge> make_cartridge(std::vector<uint8_t> pRom,
                                            gb_system::system &pSystem);

private:
  static int get_mbc_type(int pCartridgeType);
};
} // namespace cartridge

#endif // __CARTRIDGE_HPP__
