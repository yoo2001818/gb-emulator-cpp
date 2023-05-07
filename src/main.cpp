#include <iostream>
#include <memory>
#include "gb_system/system.hpp"

int main() {
  std::cout << "Hello, world!" << std::endl;
  auto system = gb_system::system();
  system.mCpu->step();
  return 0;
}
