#include "cpu.hpp"
#include "reg.hpp"
#include <concepts>
#include <utility>

#ifndef __OP_JMP_HPP__
#define __OP_JMP_HPP__

using namespace std;

namespace cpu::cond {
class cond {
public:
  static bool test(cpu &pCpu) { return false; };
};

class cond_nz : cond {
public:
  static bool test(cpu &pCpu) { return (pCpu.mRegister.f & reg::FLAG_Z) == 0; };
};

class cond_z : cond {
public:
  static bool test(cpu &pCpu) { return (pCpu.mRegister.f & reg::FLAG_Z) != 0; };
};

class cond_nc : cond {
public:
  static bool test(cpu &pCpu) { return (pCpu.mRegister.f & reg::FLAG_C) == 0; };
};

class cond_c : cond {
public:
  static bool test(cpu &pCpu) { return (pCpu.mRegister.f & reg::FLAG_C) != 0; };
};

}; // namespace cpu::cond

namespace cpu::op {
void jp_a16(cpu &pCpu);

template <typename C>
  requires is_base_of<cond::cond, C>::value
void jp_cond_a16(cpu &pCpu) {
  if (C::test(pCpu)) {
    jp_a16(pCpu);
  } else {
    pCpu.read_next16();
    pCpu.tick(2);
  }
}

void jp_hl(cpu &pCpu);
void jr_r8(cpu &pCpu);

template <typename C>
  requires is_base_of<cond::cond, C>::value
void jr_cond_r8(cpu &pCpu) {
  if (C::test(pCpu)) {
    jr_r8(pCpu);
  } else {
    pCpu.read_next8();
    pCpu.tick(2);
  }
}

void call_a16(cpu &pCpu);

template <typename C>
  requires is_base_of<cond::cond, C>::value
void call_cond_a16(cpu &pCpu) {
  if (C::test(pCpu)) {
    call_a16(pCpu);
  } else {
    pCpu.read_next16();
    pCpu.tick(2);
  }
}

void rst_nn(cpu &pCpu, uint16_t addr);
void ret(cpu &pCpu);

template <typename C>
  requires is_base_of<cond::cond, C>::value
void ret_cond(cpu &pCpu) {
  if (C::test(pCpu)) {
    pCpu.tick(1);
    ret(pCpu);
  } else {
    pCpu.tick(2);
  }
}

void reti(cpu &pCpu);
}; // namespace cpu::op

#endif // __OP_JMP_HPP_
