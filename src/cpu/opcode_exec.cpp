#include "opcode.hpp"
#include "opcode_table.hpp"
#include <iostream>

void cpu::opcode::exec_op(cpu &pCpu)
{
  auto opcode = pCpu.read_next8();
  auto fn = opcode_main_table[opcode];
  fn(pCpu);
}

void cpu::opcode::exec_op_cb(cpu &pCpu)
{
  pCpu.tick(1);
  auto opcode = pCpu.read_next8();
  auto fn = opcode_cb_table[opcode];
  fn(pCpu);
}
