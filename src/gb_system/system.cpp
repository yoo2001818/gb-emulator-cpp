#include "system.hpp"
#include <memory>

gb_system::system::system(system_type pSystemType) : mSystemType(pSystemType) {
  this->mMemoryBus = make_shared<memory::memory_bus>();
  this->mIoBus = make_shared<memory::io_bus>();
  this->mCpu = make_shared<cpu::cpu>(this->mMemoryBus);
  this->mInterrupter = make_shared<interrupter>(*this, *(this->mCpu));
  this->mCartridge = nullptr;
  this->mTimer = make_shared<timer>(*this);
  this->mWram = make_shared<wram>(*this);
  this->mHram = make_shared<hram>(*this);
  this->mPpu = make_shared<ppu>(*this);
  this->mDma = make_shared<dma>(*this);
  this->mGamepad = make_shared<gamepad>(*this);
  this->mApu = make_shared<apu::apu>(*this);
  this->reset();
}

void gb_system::system::reset() {
  if (this->mSystemType == system_type::CGB) {
    this->mCpu->reset(
        {0x11, 0x13, 0, 0xd8, 0xb0, 0x01, 0x4d, 0, 0x100, 0xfffe});
  } else {
    this->mCpu->reset(
        {0x01, 0x13, 0, 0xd8, 0xb0, 0x01, 0x4d, 0, 0x100, 0xfffe});
  }
  this->mInterrupter->reset();
  if (this->mCartridge)
    this->mCartridge->reset();
  this->mMemoryBus->reset();
  this->mIoBus->reset();
  this->mTimer->reset();
  this->mWram->reset();
  this->mHram->reset();
  this->mPpu->reset();
  this->mDma->reset();
  this->mGamepad->reset();
  this->mApu->reset();

  this->mCpu->set_on_tick([&](int pTicks) { this->tick(pTicks); });
  this->mMemoryBus->register_entry(0xff, 1, this->mIoBus);
  this->mInterrupter->register_system();
  if (this->mCartridge)
    this->mCartridge->register_system();
  this->mTimer->register_system();
  this->mWram->register_system();
  this->mHram->register_system();
  this->mPpu->register_system();
  this->mDma->register_system();
  this->mGamepad->register_system();
  this->mApu->register_system();
}

void gb_system::system::tick(int pTicks) {
  for (auto i = 0; i < pTicks; i += 1) {
    this->mTimer->tick();
    this->mPpu->tick();
    this->mDma->tick();
    this->mGamepad->tick();
    this->mApu->tick();
    if (this->mCartridge)
      this->mCartridge->tick();
  }
}
