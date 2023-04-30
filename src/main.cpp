#include <iostream>
#include "cpu/cpu.hpp"

int main() {
  std::cout << "Hello, world!" << std::endl;
  cpu::cpu cpu({});
  cpu.step();
  return 0;
}
