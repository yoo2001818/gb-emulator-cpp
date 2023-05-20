#include "timer.hpp"
#include "system.hpp"
#include "../memory/lambda_memory.hpp"

const int DIV_TICK_RATE = 256;
const int TIMA_TICK_RATES[] = { 1024, 16, 64, 256 };
const int TIMA_TICK_BITS[] = { 512, 8, 32, 128 };
const uint8_t IO_DIV = 0x04;
const uint8_t IO_TIMA = 0x05;
const uint8_t IO_TMA = 0x06;
const uint8_t IO_TAC = 0x07;

void gb_system::timer::reset()
{
  this->mClocks = 0xA7 * DIV_TICK_RATE;
  this->mTima = 0;
  this->mTma = 0;
  this->mTac = 0;
  this->mTimaDelayed = false;
}

void gb_system::timer::register_system()
{
  this->mSystem.mIoBus->register_entry(IO_DIV, make_shared<memory::lambda_memory>(
    [&](uint16_t pAddr) {
      return this->mClocks / DIV_TICK_RATE;
    },
    [&](uint16_t pAddr, uint8_t pValue) {
      this->mClocks = 0;
      if (this->mTac & 0x4) {
        auto oldBit = this->mClocks & TIMA_TICK_BITS[this->mTac & 0x3];
        if (oldBit) {
          this->mTima += 1;
          this->post_update_tima();
        }
      }
    }
  ));
  this->mSystem.mIoBus->register_entry(IO_TIMA, make_shared<memory::lambda_memory>(
    [&](uint16_t pAddr) { return this->mTima; },
    [&](uint16_t pAddr, uint8_t pValue) {
      this->mTima = pValue;
    }
  ));
  this->mSystem.mIoBus->register_entry(IO_TMA, make_shared<memory::lambda_memory>(
    [&](uint16_t pAddr) { return this->mTma; },
    [&](uint16_t pAddr, uint8_t pValue) {
      this->mTma = pValue;
    }
  ));
  this->mSystem.mIoBus->register_entry(IO_TAC, make_shared<memory::lambda_memory>(
    [&](uint16_t pAddr) { return this->mTac; },
    [&](uint16_t pAddr, uint8_t pValue) {
      auto oldTac = this->mTac;
      this->mTac = pValue;
      // Update the clock immediately
      // DMG bug - TAC increments even if enabled flag becomes false
      if (oldTac & 0x4) {
        auto oldBit = this->mClocks & TIMA_TICK_BITS[oldTac & 0x3];
        auto newBit = this->mClocks & TIMA_TICK_BITS[pValue & 0x3];
        if (!newBit && oldBit) {
          this->mTima += 1;
          this->post_update_tima();
        }
      }
    }
  ));
}

void gb_system::timer::tick()
{
  if (this->mTimaDelayed) {
    this->mTimaDelayed = false;
    this->mSystem.mInterrupter->queue_interrupt(TIMER_OVERFLOW);
  }
  if (this->mTac & 0x4) {
    // Tick the clock according to the clock
    // Note that this needs to be in sync with "clocks" variable
    // (https://gbdev.io/pandocs/Timer_Obscure_Behaviour.html)
    // Since we don't get to emulate every cycle (this is doable though),
    // we simply derive the increment count from the number of triggers
    auto nBits = TIMA_TICK_BITS[this->mTac & 0x3];
    bool oldBit = this->mClocks & nBits;
    bool newBit = (this->mClocks + 4) & nBits;
    if (oldBit && !newBit) {
      this->mTima += 1;
      this->post_update_tima();
    }
  }
  this->mClocks += 4;
}

void gb_system::timer::post_update_tima()
{
  if (this->mTima > 0xff) {
    this->mTimaDelayed = true;
    this->mTima = 0x0;
  }
}
