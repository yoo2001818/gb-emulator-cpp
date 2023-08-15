#include "cartridge.hpp"
#include "cartridge_mbc1.hpp"
#include "cartridge_mbc3.hpp"
#include "cartridge_mbc5.hpp"
#include "cartridge_raw.hpp"
#include <memory>

int cartridge::cartridge_info::get_mbc_type(int pCartridgeType) {
  switch (pCartridgeType) {
  case 0x00:
    return 0;
  case 0x01:
    return 1;
  case 0x02:
    return 1;
  case 0x03:
    return 1;
  case 0x05:
    return 2;
  case 0x06:
    return 2;
  case 0x08:
    return 0;
  case 0x09:
    return 0;
  case 0x0b:
    return 8;
  case 0x0c:
    return 8;
  case 0x0d:
    return 8;
  case 0x0f:
    return 3;
  case 0x10:
    return 3;
  case 0x11:
    return 3;
  case 0x12:
    return 3;
  case 0x13:
    return 3;
  case 0x19:
    return 5;
  case 0x1a:
    return 5;
  case 0x1b:
    return 5;
  case 0x1c:
    return 5;
  case 0x1d:
    return 5;
  case 0x1e:
    return 5;
  case 0x20:
    return 6;
  case 0x22:
    return 7;
  case 0xfc:
    return 9;
  case 0xfd:
    return 10;
  case 0xfe:
    return 11;
  case 0xff:
    return 12;
  default:
    return 0;
  }
}

int RAM_BANKS[] = {0, 0, 1, 4, 16, 8};

cartridge::cartridge_info::cartridge_info(std::vector<uint8_t> pRom) {
  // 0134 - 0143 Title
  // 0143 - CGB flag
  // 0146 - SGB flag
  // 0147 - Cartridge type
  // 0148 - ROM size
  // 0149 - RAM size
  auto title = std::string(pRom.begin() + 0x0134, pRom.begin() + 0x0143);
  auto cgbFlag = pRom[0x0143];
  bool supportsCGB = cgbFlag & 0x80;
  bool requiresCGB = cgbFlag & 0x40;
  auto sgbFlag = pRom[0x0146];
  bool supportsSGB = sgbFlag == 0x03;

  auto cartridgeType = pRom[0x0147];
  auto mbcType = get_mbc_type(cartridgeType);
  this->mbcType = mbcType;
  this->ramSize = RAM_BANKS[pRom[0x0149]] * 8 * 1024;
  this->romSize = (2 << pRom[0x0148]) * 16 * 1024;
  // MBC2 has 512 bytes of RAM internally
  if (this->mbcType == 2) {
    this->ramSize = 512;
  }
  this->title = title;
  this->supportsCGB = supportsCGB;
  this->requiresCGB = requiresCGB;
  this->supportsSGB = supportsSGB;
}

std::shared_ptr<cartridge::cartridge>
cartridge::cartridge_info::make_cartridge(std::vector<uint8_t> pRom,
                                          gb_system::system &pSystem) {
  switch (this->mbcType) {
  case 0:
    return std::make_shared<cartridge_raw>(pRom, pSystem);
  case 1:
    return std::make_shared<cartridge_mbc1>(
        pRom, std::vector<uint8_t>(this->ramSize), pSystem);
  case 3:
    return std::make_shared<cartridge_mbc3>(
        pRom, std::vector<uint8_t>(this->ramSize), pSystem);
  case 5:
    return std::make_shared<cartridge_mbc5>(
        pRom, std::vector<uint8_t>(this->ramSize), pSystem);
  default:
    // Unsupported
    return nullptr;
  }
}
