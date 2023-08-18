#include "apu.hpp"
#include "system.hpp"
#include <algorithm>
#include <cmath>

void gb_system::apu::envelope_psg_module::reset() {
  this->mInitialVolume = 0;
  this->mCurrentVolume = 0;
  this->mIncreasing = false;
  this->mPace = 0;
  this->mClock = 0;
}
void gb_system::apu::envelope_psg_module::trigger() {
  this->mCurrentVolume = this->mInitialVolume;
  this->mClock = 0;
}
void gb_system::apu::envelope_psg_module::step(int pClocks) {
  auto width = 65536 * this->mPace;
  this->mClock += pClocks;
  if (this->mPace > 0 && this->mClock >= width) {
    this->mClock = 0;
    if (this->mIncreasing) {
      this->mCurrentVolume = std::min(this->mCurrentVolume + 1, 0xf);
    } else {
      this->mCurrentVolume = std::max(this->mCurrentVolume - 1, 0);
    }
  }
}
int gb_system::apu::envelope_psg_module::read(uint16_t pAddr) {
  if (pAddr == 2) {
    // NR12 - Volume & envelope
    int output = 0x100;
    output |= this->mPace & 0x7;
    if (this->mIncreasing)
      output |= 0x8;
    output |= (this->mInitialVolume & 0xf) << 4;
    return output;
  }
  return 0;
}
void gb_system::apu::envelope_psg_module::write(uint16_t pAddr,
                                                uint8_t pValue) {
  if (pAddr == 2) {
    // NR12 - Volume & envelope
    this->mPace = pValue & 0x7;
    this->mIncreasing = (pValue & 0x8) > 0;
    this->mInitialVolume = (pValue >> 4) & 0xf;
  }
}
float gb_system::apu::envelope_psg_module::get() {
  return this->mCurrentVolume / (float)0xf;
}
int gb_system::apu::envelope_psg_module::get_next_clocks(int pClocks) {
  if (this->mPace == 0)
    return pClocks;
  int width = 65536 * this->mPace;
  int remaining = width - this->mClock;
  return std::min(pClocks, remaining);
}

void gb_system::apu::length_psg_module::reset() {
  this->mEnabled = false;
  this->mInitialLength = 0;
  this->mCurrentLength = 0;
  this->mClock = 0;
}
void gb_system::apu::length_psg_module::trigger() {
  this->mCurrentLength = this->mInitialLength;
  this->mClock = 0;
}
void gb_system::apu::length_psg_module::step(int pClocks, bool *pEnabled) {
  int width = 16384;
  this->mClock += pClocks;
  if (this->mEnabled && this->mClock >= width) {
    this->mClock = 0;
    this->mCurrentLength = std::min(this->mCurrentLength + 1, 64);
    if (this->mCurrentLength == 64) {
      *pEnabled = false;
    }
  }
}
int gb_system::apu::length_psg_module::read(uint16_t pAddr) {
  if (pAddr == 4) {
    // NR14 - Wavelength high & control
    int output = 0x100;
    if (this->mEnabled)
      output |= 0x8;
    return output;
  }
  return 0;
}
void gb_system::apu::length_psg_module::write(uint16_t pAddr, uint8_t pValue) {
  if (pAddr == 1) {
    this->mInitialLength = pValue & 0x1f;
  } else if (pAddr == 4) {
    // NR14 - Wavelength high & control
    this->mEnabled = (pValue & 0x40) > 0;
  }
}
int gb_system::apu::length_psg_module::get_next_clocks(int pClocks) {
  if (!this->mEnabled)
    return pClocks;
  int width = 16384;
  int remaining = width - this->mClock;
  return std::min(pClocks, remaining);
}

void gb_system::apu::sweep_psg_module::reset() {
  this->mInitialPace = 0;
  this->mPace = 0;
  this->mIncreasing = false;
  this->mSlope = 0;
  this->mClock = 0;
}
void gb_system::apu::sweep_psg_module::trigger() {
  this->mClock = 0;
  this->mPace = this->mInitialPace;
}
void gb_system::apu::sweep_psg_module::step(int pClocks, int *pWavelength,
                                            bool *pEnabled) {
  int width = 32768 * this->mPace;
  this->mClock += pClocks;
  if (this->mPace > 0 && this->mClock >= width) {
    this->mClock = 0;
    int wavelength = *pWavelength;
    int nextWavelength = wavelength + (wavelength >> this->mSlope) *
                                          (this->mIncreasing ? 1 : -1);
    if (nextWavelength >= 0x7ff) {
      *pEnabled = false;
      *pWavelength = 0x7ff;
    } else {
      *pWavelength = nextWavelength;
    }
  }
}
int gb_system::apu::sweep_psg_module::read(uint16_t pAddr) {
  if (pAddr == 0) {
    // NR10 - Sweep
    int output = 0x100;
    output |= this->mSlope & 0x7;
    if (!this->mIncreasing)
      output |= 0x8;
    output |= (this->mInitialPace & 0x7) << 4;
    return output;
  }
  return 0;
}
void gb_system::apu::sweep_psg_module::write(uint16_t pAddr, uint8_t pValue) {
  if (pAddr == 0) {
    // NR10 - Sweep
    this->mSlope = pValue & 0x7;
    this->mIncreasing = (pValue & 0x8) > 0;
    this->mInitialPace = (pValue >> 4) & 0x7;
    if (this->mInitialPace == 0) {
      this->mPace = 0;
    } else if (this->mPace == 0) {
      this->mPace = this->mInitialPace;
    }
  }
}
int gb_system::apu::sweep_psg_module::get_next_clocks(int pClocks) {
  if (this->mPace == 0)
    return pClocks;
  int width = 32768 * this->mPace;
  int remaining = width - this->mClock;
  return std::min(pClocks, remaining);
}

void gb_system::apu::square_psg::reset() {
  this->mOutput = 0;
  this->mEnabled = false;
  this->mPhase = 0;
  this->mPhaseClock = 0;
  this->mWavelength = 0;
  this->mDutyCycle = 0;
  this->mSweep.reset();
  this->mEnvelope.reset();
  this->mLength.reset();
}
void gb_system::apu::square_psg::trigger() {
  this->mOutput = 0;
  this->mEnabled = true;
  this->mPhase = 0;
  this->mPhaseClock = 0;
  this->mSweep.trigger();
  this->mEnvelope.trigger();
  this->mLength.trigger();
}

static const int SQUARE_PSG_DUTY_CYCLE_TABLE[] = {0xFE, 0x7E, 0x78, 0x81};
void gb_system::apu::square_psg::step(int pClocks) {
  int remainingClocks = pClocks;
  while (remainingClocks > 0) {
    if (!this->mEnabled)
      break;
    // Calculate clocks for each trigger
    int phaseWidth = 4 * (2048 - this->mWavelength);
    int phaseRemaining = phaseWidth - this->mPhaseClock;

    // Calculate the smallest trigger
    int consumedClocks = std::min(phaseRemaining, remainingClocks);
    if (this->mHasSweep)
      consumedClocks = this->mSweep.get_next_clocks(consumedClocks);
    consumedClocks = this->mEnvelope.get_next_clocks(consumedClocks);
    consumedClocks = this->mLength.get_next_clocks(consumedClocks);

    this->mPhaseClock += consumedClocks;
    if (this->mPhaseClock >= phaseWidth) {
      this->mPhaseClock = 0;
      this->mPhase = (this->mPhase + 1) % 8;
    }
    if (this->mHasSweep)
      this->mSweep.step(consumedClocks, &this->mWavelength, &this->mEnabled);
    this->mEnvelope.step(consumedClocks);
    this->mLength.step(consumedClocks, &this->mEnabled);

    remainingClocks -= consumedClocks;
  }
  // Calculate current mOutput
  if (this->mEnabled) {
    int signal =
        (SQUARE_PSG_DUTY_CYCLE_TABLE[this->mDutyCycle] >> (7 - this->mPhase)) &
        1;
    this->mOutput = (signal ? -1.0f : 1.0f) * this->mEnvelope.get();
  } else {
    this->mOutput = 0.0f;
  }
}
uint8_t gb_system::apu::square_psg::read(uint16_t pAddr) {
  int output = 0;
  switch (pAddr) {
  case 1:
    // NR11 - Length timer & duty cycle
    output = 0x100 | ((this->mDutyCycle & 0x3) << 6);
    break;
  case 2:
    // NR13 - Wavelength low
    output = 0x100 | (this->mWavelength & 0xff);
    break;
  case 3:
    // NR14 - Wavelength high & control
    output = 0x100 | ((this->mWavelength >> 8) & 0x7);
    break;
  }
  if (this->mHasSweep)
    output |= this->mSweep.read(pAddr);
  output |= this->mEnvelope.read(pAddr);
  output |= this->mLength.read(pAddr);
  if (output & 0x100)
    return output & 0xff;
  return 0xff;
}
void gb_system::apu::square_psg::write(uint16_t pAddr, uint8_t pValue) {
  switch (pAddr) {
  case 1:
    // NR11 - Length timer & duty cycle
    this->mDutyCycle = (pValue >> 6) & 0x3;
    break;
  case 2:
    // NR12 - Wavelength low
    this->mWavelength = (this->mWavelength & 0x700) | (pValue & 0xff);
    break;
  case 3:
    // NR13 - Wavelength high & control
    this->mWavelength = (this->mWavelength & 0xff) | ((pValue & 0x7) << 8);
    if (pValue & 0x80)
      this->trigger();
    break;
  }
  if (this->mHasSweep)
    this->mSweep.write(pAddr, pValue);
  this->mEnvelope.write(pAddr, pValue);
  this->mLength.write(pAddr, pValue);
}
float gb_system::apu::square_psg::get() { return this->mOutput; }
bool gb_system::apu::square_psg::enabled() { return this->mEnabled; }

void gb_system::apu::noise_psg::reset() {
  this->mOutput = 0;
  this->mEnabled = false;
  this->mPhaseClock = 0;
  this->mClockShift = 0;
  this->mClockDivider = 0;
  this->mLfsr = 0;
  this->mLfsr7Bit = false;
  this->mEnvelope.reset();
  this->mLength.reset();
}
void gb_system::apu::noise_psg::trigger() {
  this->mOutput = 0;
  this->mEnabled = true;
  this->mPhaseClock = 0;
  this->mLfsr = 0;
  this->mEnvelope.trigger();
  this->mLength.trigger();
}
void gb_system::apu::noise_psg::step(int pClocks) {
  int remainingClocks = pClocks;
  while (remainingClocks > 0) {
    if (!this->mEnabled)
      break;
    // Calculate clocks for each trigger
    // The clock is 262144 / (r * (2^s)) Hz, where r is 0.5 when r = 0
    // Meaning that this is triggered every 16 * r * 2^s clocks.
    float r = this->mClockDivider * 2;
    if (r == 0)
      r = 1;
    int phaseWidth = 8 * r * (1 << this->mClockShift);
    int phaseRemaining = phaseWidth - this->mPhaseClock;

    // Calculate the smallest trigger
    int consumedClocks = std::min(phaseRemaining, remainingClocks);
    consumedClocks = this->mEnvelope.get_next_clocks(consumedClocks);
    consumedClocks = this->mLength.get_next_clocks(consumedClocks);

    this->mPhaseClock += consumedClocks;
    if (this->mPhaseClock >= phaseWidth) {
      this->mPhaseClock = 0;

      // Update LFSR
      int setBit = this->mLfsr7Bit ? 0x8080 : 0x8000;
      int lfsr = this->mLfsr;
      lfsr = lfsr | (((lfsr & 1) != ((lfsr >> 1) & 1)) ? 0 : setBit);
      lfsr = lfsr >> 1;
      this->mLfsr = lfsr;
    }
    this->mEnvelope.step(consumedClocks);
    this->mLength.step(consumedClocks, &this->mEnabled);

    remainingClocks -= consumedClocks;
  }
  // Calculate current mOutput
  if (this->mEnabled) {
    int signal = this->mLfsr & 1;
    this->mOutput = (signal ? -1.0f : 1.0f) * this->mEnvelope.get();
  } else {
    this->mOutput = 0.0f;
  }
}
uint8_t gb_system::apu::noise_psg::read(uint16_t pAddr) {
  int output = 0;
  switch (pAddr) {
  case 3:
    // NR13 - Frequency & randomness
    output |= 0x100;
    output |= (this->mClockShift & 0xf) << 4;
    if (this->mLfsr7Bit)
      output |= 0x8;
    output |= this->mClockDivider & 0x7;
    break;
  }
  output |= this->mEnvelope.read(pAddr);
  output |= this->mLength.read(pAddr);
  if (output & 0x100)
    return output & 0xff;
  return 0xff;
}
void gb_system::apu::noise_psg::write(uint16_t pAddr, uint8_t pValue) {
  switch (pAddr) {
  case 3:
    // NR13 - Frequency & randomness
    this->mClockShift = (pValue >> 4) & 0xf;
    this->mLfsr7Bit = (pValue & 0x8) != 0;
    this->mClockDivider = pValue & 0x7;
    break;
  case 4:
    // NR44 - Control
    if (pValue & 0x80)
      this->trigger();
    break;
  }
  this->mEnvelope.write(pAddr, pValue);
  this->mLength.write(pAddr, pValue);
}
float gb_system::apu::noise_psg::get() { return this->mOutput; }
bool gb_system::apu::noise_psg::enabled() { return this->mEnabled; }

void gb_system::apu::pcm_psg::reset() {
  this->mOutput = 0;
  this->mDacEnabled = false;
  this->mEnabled = false;

  this->mPhase = 0;
  this->mPhaseClock = 0;
  this->mWavelength = 0;
  this->mOutputLevel = 0;
  this->mLength.reset();
}
void gb_system::apu::pcm_psg::trigger() {
  this->mOutput = 0;
  this->mEnabled = true;
  this->mDacEnabled = true;
  this->mPhase = 0;
  this->mPhaseClock = 0;
  this->mLength.trigger();
}
static const float PCM_PSG_OUTPUT_LEVELS[] = {0.0f, 1.0f, 0.5f, 0.25f};
void gb_system::apu::pcm_psg::step(int pClocks) {
  int remainingClocks = pClocks;
  while (remainingClocks > 0) {
    if (!this->mEnabled || !this->mDacEnabled)
      break;
    // Calculate clocks for each trigger
    int phaseWidth = 2 * (2048 - this->mWavelength);
    int phaseRemaining = phaseWidth - this->mPhaseClock;

    // Calculate the smallest trigger
    int consumedClocks = std::min(phaseRemaining, remainingClocks);
    consumedClocks = this->mLength.get_next_clocks(consumedClocks);

    this->mPhaseClock += consumedClocks;
    if (this->mPhaseClock >= phaseWidth) {
      this->mPhaseClock = 0;
      this->mPhase = (this->mPhase + 1) % 32;
    }
    this->mLength.step(consumedClocks, &this->mEnabled);

    remainingClocks -= consumedClocks;
  }
  // Calculate current mOutput
  if (this->mEnabled && this->mDacEnabled) {
    int readAddr = this->mPhase >> 1;
    int readNibble = this->mPhase & 1;
    int byte = this->mWaveTable[readAddr];
    float signal = ((byte >> (readNibble ? 0 : 4)) & 0xf) / 15.0f;
    this->mOutput =
        (signal * 2.0f - 1.0f) * PCM_PSG_OUTPUT_LEVELS[this->mOutputLevel];
  } else {
    this->mOutput = 0.0f;
  }
}
uint8_t gb_system::apu::pcm_psg::read(uint16_t pAddr) {
  int output = 0;
  switch (pAddr) {
  case 0:
    // NR30 - DAC Enable
    output |= 0x100;
    if (this->mDacEnabled)
      output |= 0x80;
    break;
  case 2:
    // NR32 - Output level
    output = 0x100 | ((this->mOutputLevel & 0x3) << 5);
    break;
  case 3:
    // NR33 - Wavelength low
    output = 0x100 | (this->mWavelength & 0xff);
    break;
  case 4:
    // NR34 - Wavelength high & control
    output = 0x100 | ((this->mWavelength >> 8) & 0x7);
    break;
  }
  output |= this->mLength.read(pAddr);
  if (output & 0x100)
    return output & 0xff;
  return 0xff;
}
void gb_system::apu::pcm_psg::write(uint16_t pAddr, uint8_t pValue) {
  switch (pAddr) {
  case 0:
    // NR30 - DAC Enable
    this->mDacEnabled = (pValue & 0x80);
    break;
  case 2:
    // NR32 - Output level
    this->mOutputLevel = (pValue >> 5) & 0x3;
    break;
  case 3:
    // NR33 - Wavelength low
    this->mWavelength = (this->mWavelength & 0x700) | (pValue & 0xff);
    break;
  case 4:
    // NR34 - Wavelength high & control
    this->mWavelength = (this->mWavelength & 0xff) | ((pValue & 0x7) << 8);
    if (pValue & 0x80)
      this->trigger();
    break;
  }
  this->mLength.write(pAddr, pValue);
}
float gb_system::apu::pcm_psg::get() { return this->mOutput; }
bool gb_system::apu::pcm_psg::enabled() { return this->mEnabled; }
std::array<uint8_t, 0x10> &gb_system::apu::pcm_psg::wave_table() {
  return this->mWaveTable;
}

gb_system::apu::apu::apu(gb_system::system &pSystem)
    : mPsg1(true), mPsg2(false), mSystem(pSystem) {}
void gb_system::apu::apu::reset() {
  this->mBuffer.fill(0.0f);
  this->mClocks = 0;
  this->mBufferPos = 0;
  this->mPsg1.reset();
  this->mPsg2.reset();
  this->mPsg3.reset();
  this->mPsg4.reset();
  this->mNr50 = 0;
  this->mNr51 = 0;
  this->mNr52 = 0;
}
const uint8_t IO_APU = 0x00;
void gb_system::apu::apu::register_system() {
  this->mSystem.mIoBus->register_entry(IO_APU, 0x30, this->shared_from_this());
}
float gb_system::apu::apu::get_output(int pChannel) {
  // NR52 Bit 7:: All sound on/off
  if ((this->mNr52 & 0x80) == 0)
    return 0.0f;
  // NR51: Sound panning
  int nr51 = this->mNr51;
  // NR50: Master volume, VIN panning
  int nr50 = this->mNr50;

  float output = 0.0f;
  if (nr51 & (1 << (pChannel * 4)))
    output += this->mPsg1.get();
  if (nr51 & (1 << (pChannel * 4 + 1)))
    output += this->mPsg2.get();
  if (nr51 & (1 << (pChannel * 4 + 2)))
    output += this->mPsg3.get();
  if (nr51 & (1 << (pChannel * 4 + 3)))
    output += this->mPsg4.get();

  if (pChannel == 0) {
    output *= ((nr50 >> 4) & 0x7) / 7.0f;
  } else {
    output *= (nr50 & 0x7) / 7.0f;
  }
  return output / 4.0f;
};
void gb_system::apu::apu::tick() {
  this->mClocks += 4;
  int futurePos = this->mClocks / CLOCKS_PER_SAMPLE;
  while (this->mBufferPos < futurePos) {
    if (this->mBufferPos >= this->mBuffer.size())
      break;
    // Step
    // NR52 Bit 7: All sound on/off
    if (this->mNr52 & 0x80) {
      this->mPsg1.step(CLOCKS_PER_SAMPLE);
      this->mPsg2.step(CLOCKS_PER_SAMPLE);
      this->mPsg3.step(CLOCKS_PER_SAMPLE);
      this->mPsg4.step(CLOCKS_PER_SAMPLE);
    }
    for (int channel = 0; channel < 2; channel += 1) {
      int offset = SAMPLE_SIZE * channel;
      this->mBuffer[offset + this->mBufferPos] = this->get_output(channel);
    }
    this->mBufferPos += 1;
  }
}
std::array<uint16_t, gb_system::apu::apu::SAMPLE_SIZE * 2> &
gb_system::apu::apu::finalize() {
  this->mBufferPos = 0;
  this->mClocks = 0;
  return this->mBuffer;
}
uint8_t gb_system::apu::apu::read(uint16_t pAddr) {
  if (pAddr < 5) {
    return this->mPsg1.read(pAddr % 5);
  } else if (pAddr < 10) {
    return this->mPsg2.read(pAddr % 5);
  } else if (pAddr < 15) {
    return this->mPsg3.read(pAddr % 5);
  } else if (pAddr < 20) {
    return this->mPsg4.read(pAddr % 5);
  } else if (pAddr >= 0x20) {
    return this->mPsg3.wave_table()[pAddr - 0x20];
  }
  switch (pAddr) {
  case 0x14:
    return this->mNr50;
  case 0x15:
    return this->mNr51;
  case 0x16: {
    int output = this->mNr52;
    if (this->mPsg1.enabled())
      output |= 1;
    if (this->mPsg2.enabled())
      output |= 2;
    if (this->mPsg3.enabled())
      output |= 4;
    if (this->mPsg4.enabled())
      output |= 8;
    return output;
  }
  default:
    return 0xff;
  }
}
void gb_system::apu::apu::write(uint16_t pAddr, uint8_t pValue) {
  if (pAddr < 5) {
    this->mPsg1.write(pAddr % 5, pValue);
  } else if (pAddr < 10) {
    this->mPsg2.write(pAddr % 5, pValue);
  } else if (pAddr < 15) {
    this->mPsg3.write(pAddr % 5, pValue);
  } else if (pAddr < 20) {
    this->mPsg4.write(pAddr % 5, pValue);
  } else if (pAddr >= 0x20) {
    this->mPsg3.wave_table()[pAddr - 0x20] = pValue;
  } else {
    switch (pAddr) {
    case 0x14:
      this->mNr50 = pValue;
      break;
    case 0x15:
      this->mNr51 = pValue;
      break;
    case 0x16:
      this->mNr52 = pValue & 0x80;
      break;
    }
  }
}
