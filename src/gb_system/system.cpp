#include "system.hpp"

gb_system::system::system()
{
  this->mMemoryBus = make_shared<memory::memory_bus>();
  this->mIoBus = make_shared<memory::io_bus>();
  this->mCpu = make_shared<cpu::cpu>(this->mMemoryBus);
  this->mInterrupter = make_shared<interrupter>(*this, *(this->mCpu));
  this->reset();
}

void gb_system::system::reset()
{
  this->mCpu->reset();
  this->mInterrupter->reset();
  this->mMemoryBus->reset();
  this->mIoBus->reset();

  this->mCpu->setOnTick([&](int pTicks) {
    // ...
  });
  this->mMemoryBus->register_entry(0xff, 1, this->mIoBus);
}
