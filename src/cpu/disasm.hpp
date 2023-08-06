#include "cpu.hpp"

#ifndef __DISASM_HPP__
#define __DISASM_HPP__

namespace cpu
{
  namespace opcode
  {
    std::string disasm_op_cb(cpu &pCpu);
    std::string disasm_op(cpu &pCpu);
  }
}

#endif // __DISASM_HPP__
