#include <utility>
#include <concepts>
#include "cpu.hpp"
#include "reg.hpp"

#ifndef __OP_JMP_HPP__
#define __OP_JMP_HPP__

using namespace std;

namespace cpu::cond
{
  class cond
  {
    public:
    static bool test(cpu &pCpu) { return false; };
  };

  class cond_nz : cond
  {
    public:
    static bool test(cpu &pCpu) { return false; };
  };

};

namespace cpu::op
{
  void jp_a16(cpu &pCpu);

  template <typename C>
    requires is_base_of<cond::cond, C>::value
  void jp_cond_a16(cpu &pCpu)
  {
    if (C::test(pCpu)) {
      jp_a16(pCpu);
    } else {
      pCpu.skip(2);
      pCpu.tick(3);
    }
  }

  void jp_hl(cpu &pCpu);
  void jr_r8(cpu &pCpu);

  template <typename C>
    requires is_base_of<cond::cond, C>::value
  void jr_cond_r8(cpu &pCpu)
  {
    if (C::test(pCpu)) {
      jr_r8(pCpu);
    } else {
      pCpu.skip(1);
      pCpu.tick(2);
    }
  }

  void call_a16(cpu &pCpu);

  template <typename C>
    requires is_base_of<cond::cond, C>::value
  void call_cond_a16(cpu &pCpu)
  {
    if (C::test(pCpu)) {
      call_a16(pCpu);
    } else {
      pCpu.skip(2);
      pCpu.tick(3);
    }
  }

  void rst_nn(cpu &pCpu, uint16_t addr);
  void ret(cpu &pCpu);

  template <typename C>
    requires is_base_of<cond::cond, C>::value
  void ret_cond(cpu &pCpu)
  {
    if (C::test(pCpu)) {
      ret(pCpu);
    } else {
      pCpu.tick(2);
    }
  }

  void reti(cpu &pCpu);
};

#endif // __OP_JMP_HPP_
