#include "../memory/memory.hpp"
#include "component.hpp"
#include <array>
#include <cstdint>
#include <memory>

#ifndef __APU_HPP__
#define __APU_HPP__

namespace gb_system {
class system;
namespace apu {
class psg_module {
public:
  virtual void reset() = 0;
  virtual void trigger() = 0;
  virtual int read(uint16_t pAddr) = 0;
  virtual void write(uint16_t pAddr, uint8_t pValue) = 0;
  virtual int get_next_clocks(int pClocks) = 0;
  virtual ~psg_module() = default;
};
class envelope_psg_module : public psg_module {
public:
  void reset() override;
  void trigger() override;
  void step(int pClocks);
  int read(uint16_t pAddr) override;
  void write(uint16_t pAddr, uint8_t pValue) override;
  int get_next_clocks(int pClocks) override;
  float get();

private:
  int mInitialVolume;
  int mCurrentVolume;
  bool mIncreasing;
  int mPace;
  int mClock;
};
class length_psg_module : public psg_module {
public:
  void reset() override;
  void trigger() override;
  void step(int pClocks, bool *pEnabled);
  int read(uint16_t pAddr) override;
  void write(uint16_t pAddr, uint8_t pValue) override;
  int get_next_clocks(int pClocks) override;

private:
  bool mEnabled;
  int mInitialLength;
  int mCurrentLength;
  int mClock;
};
class sweep_psg_module : public psg_module {
public:
  void reset() override;
  void trigger() override;
  void step(int pClocks, int *pWavelength, bool *pEnabled);
  int read(uint16_t pAddr) override;
  void write(uint16_t pAddr, uint8_t pValue) override;
  int get_next_clocks(int pClocks) override;

private:
  int mInitialPace;
  int mPace;
  bool mIncreasing;
  int mSlope;
  int mClock;
};
class psg : public memory::memory {
public:
  virtual void reset() = 0;
  virtual void trigger() = 0;
  virtual void step(int pClocks) = 0;
  virtual uint8_t read(uint16_t pAddr) = 0;
  virtual void write(uint16_t pAddr, uint8_t pValue) = 0;
  virtual float get() = 0;
  virtual bool enabled() = 0;
  virtual ~psg() = default;
};
class square_psg : public psg {
public:
  square_psg(bool pHasSweep) : mHasSweep(pHasSweep){};
  void reset() override;
  void trigger() override;
  void step(int pClocks) override;
  uint8_t read(uint16_t pAddr) override;
  void write(uint16_t pAddr, uint8_t pValue) override;
  float get() override;
  bool enabled() override;

private:
  float mOutput;
  bool mHasSweep = false;
  bool mEnabled = false;
  int mPhase;
  int mPhaseClock;
  int mWavelength;
  int mDutyCycle;
  sweep_psg_module mSweep;
  envelope_psg_module mEnvelope;
  length_psg_module mLength;
};
class noise_psg : public psg {
public:
  void reset() override;
  void trigger() override;
  void step(int pClocks) override;
  uint8_t read(uint16_t pAddr) override;
  void write(uint16_t pAddr, uint8_t pValue) override;
  float get() override;
  bool enabled() override;

private:
  float mOutput;
  bool mEnabled = false;
  int mPhaseClock;
  int mClockShift;
  int mClockDivider;
  int mLfsr;
  bool mLfsr7Bit;
  envelope_psg_module mEnvelope;
  length_psg_module mLength;
};
class pcm_psg : public psg {
public:
  void reset() override;
  void trigger() override;
  void step(int pClocks) override;
  uint8_t read(uint16_t pAddr) override;
  void write(uint16_t pAddr, uint8_t pValue) override;
  float get() override;
  bool enabled() override;
  std::array<uint8_t, 0x10> &wave_table();

private:
  float mOutput;
  bool mDacEnabled = false;
  bool mEnabled = false;
  int mPhase;
  int mPhaseClock;
  int mWavelength;
  int mOutputLevel;
  std::array<uint8_t, 0x10> mWaveTable;
  length_psg_module mLength;
};
class apu : public component,
            public memory::memory,
            public std::enable_shared_from_this<apu> {
public:
  static const int SAMPLE_SIZE = 32768;
  static const int CLOCKS_PER_SAMPLE = 4194304 / 32768;
  apu(system &pSystem);
  void reset();
  void register_system();
  void tick();
  uint8_t read(uint16_t pAddr);
  void write(uint16_t pAddr, uint8_t pValue);
  std::array<uint16_t, SAMPLE_SIZE * 2> &finalize();

private:
  std::array<uint16_t, SAMPLE_SIZE * 2> mBuffer;
  int mBufferPos;
  int mClocks;
  uint8_t mNr50;
  uint8_t mNr51;
  uint8_t mNr52;
  square_psg mPsg1;
  square_psg mPsg2;
  pcm_psg mPsg3;
  noise_psg mPsg4;
  float get_output(int pChannel);
  system &mSystem;
};
}; // namespace apu
}; // namespace gb_system

#endif // __APU_HPP__
