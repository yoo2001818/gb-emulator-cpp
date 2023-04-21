#include "op_jmp.hpp"

void cpu::op::jp_a16(cpu &pCpu)
{
  auto addr = pCpu.read_next16();
  pCpu.mRegister.pc = addr;
  pCpu.tick(4);
}

void cpu::op::jp_hl(cpu &pCpu)
{
  auto addr = pCpu.mRegister.hl();
  pCpu.mRegister.pc = addr;
  pCpu.tick(1);
}

void cpu::op::jr_r8(cpu &pCpu)
{
  int offset = pCpu.read_next8();
  if (offset & 0x80) {
    offset = -((~offset + 1) & 0xff);
  }
  uint16_t addr = (pCpu.mRegister.pc + offset) & 0xffff;
  pCpu.mRegister.pc = addr;
  pCpu.tick(3);
}

void cpu::op::call_a16(cpu &pCpu)
{
  auto nextAddr = pCpu.read_next16();
  pCpu.tick(3);
  auto pushAddr = pCpu.mRegister.pc + 1;
  pCpu.push16(pushAddr);
  pCpu.tick(3);
  pCpu.mRegister.pc = nextAddr;
}

void cpu::op::rst_nn(cpu &pCpu, uint16_t addr)
{
  pCpu.tick(1);
  auto pushAddr = pCpu.mRegister.pc + 1;
  pCpu.push16(pushAddr);
  pCpu.tick(3);
  pCpu.mRegister.pc = addr;
}

void cpu::op::ret(cpu &pCpu)
{
  auto nextAddr = pCpu.pop16();
  pCpu.tick(4);
  pCpu.mRegister.pc = nextAddr;
}

void cpu::op::reti(cpu &pCpu)
{
  auto nextAddr = pCpu.pop16();
  pCpu.tick(4);
  pCpu.mRegister.pc = nextAddr;
  pCpu.mIsInterruptsEnabled = true;
  pCpu.mIsInterruptsEnabledNext = true;
}
