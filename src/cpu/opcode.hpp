#include <array>
#include <ostream>

#include "cpu.hpp"

#ifndef __OPCODE_HPP__
#define __OPCODE_HPP__

using namespace std;

namespace cpu {
namespace opcode {
void exec_op(cpu &pCpu);
void exec_op_cb(cpu &pCpu);
}; // namespace opcode
}; // namespace cpu

#endif // __OPCODE_HPP__
