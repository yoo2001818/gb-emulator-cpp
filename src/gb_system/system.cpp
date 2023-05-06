#include "system.hpp"

gb_system::system::system()
{
  this->mMemoryBus = make_shared<memory::memory_bus>();
  this->mIoBus = make_shared<memory::io_bus>();
  this->mCpu = make_shared<cpu::cpu>(this->mMemoryBus);
  this->mInterrupter = make_shared<interrupter>(*this, *(this->mCpu));
  this->mTimer = make_shared<timer>(*this);
  this->reset();
}

void gb_system::system::reset()
{
  this->mCpu->reset();
  this->mInterrupter->reset();
  this->mMemoryBus->reset();
  this->mIoBus->reset();
  this->mTimer->reset();

  this->mCpu->setOnTick([&](int pTicks) {
    this->tick(pTicks);
  });
  this->mMemoryBus->register_entry(0xff, 1, this->mIoBus);
  this->mInterrupter->register_system();
  this->mTimer->register_system();
}

void gb_system::system::tick(int pTicks)
{

}
