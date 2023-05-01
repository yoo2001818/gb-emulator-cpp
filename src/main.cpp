#include <iostream>
#include <memory>
#include "cpu/cpu.hpp"
#include "memory/memory_bus.hpp"
#include "memory/lambda_memory.hpp"

int main() {
  std::cout << "Hello, world!" << std::endl;
  auto mem = make_shared<memory::memory_bus>();
  mem->register_entry(0, 0xff, make_shared<memory::lambda_memory>(
    [](uint16_t pAddr) {
      std::cout << "Read " << pAddr << std::endl;
      return 0;
    },
    [](uint16_t pAddr, uint8_t pValue) { return; }
  ));
  cpu::cpu cpu(mem);
  cpu.step();
  return 0;
}
