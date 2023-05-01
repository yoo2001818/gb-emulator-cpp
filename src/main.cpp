#include <iostream>
#include <memory>
#include "cpu/cpu.hpp"
#include "memory/memory_bus.hpp"

int main() {
  std::cout << "Hello, world!" << std::endl;
  auto mem = make_shared<memory::memory_bus>();
  cpu::cpu cpu(mem);
  cpu.step();
  return 0;
}
