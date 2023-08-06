#include "disasm.hpp"
#include "disasm_table.hpp"

std::string cpu::opcode::disasm_op_cb(cpu &pCpu)
{
  auto opcode = pCpu.read_next8();
  auto fn = disasm_cb_table[opcode];
  return fn(pCpu);
}

std::string cpu::opcode::disasm_op(cpu &pCpu)
{
  auto prevPc = pCpu.mRegister.pc;
  auto opcode = pCpu.read_next8();
  auto fn = disasm_main_table[opcode];
  auto result = fn(pCpu);
  pCpu.mRegister.pc = prevPc;
  return result;
}
