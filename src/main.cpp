#include <iostream>
#include "cpu/cpu.hpp"
#include "cpu/op.hpp"

int main() {
  std::cout << "Hello, world!" << std::endl;
  cpu::cpu cpu({});
  cpu::op::ld8<cpu::reg::reg8_a, cpu::reg::reg8_b>(cpu);
  return 0;
}
