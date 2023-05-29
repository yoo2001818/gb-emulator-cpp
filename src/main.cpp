#include <iostream>
#include <memory>
#include "gb_system/system.hpp"

int main() {
  std::cout << "Hello, world!" << std::endl;
  auto system = gb_system::system(gb_system::system_type::CGB);
  system.mCpu->step();
  return 0;
}
