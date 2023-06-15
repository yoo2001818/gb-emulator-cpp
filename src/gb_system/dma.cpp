#include "dma.hpp"
#include "system.hpp"
#include "../memory/lambda_memory.hpp"

const uint8_t IO_DMA = 0x46;

void gb_system::dma::reset()
{
  this->mSrc = 0;
  this->mPos = -1;
}

void gb_system::dma::register_system()
{
  this->mSystem.mIoBus->register_entry(IO_DMA, make_shared<memory::lambda_memory>(
                                                   [&](uint16_t pAddr)
                                                   {
                                                     return 0xff;
                                                   },
                                                   [&](uint16_t pAddr, uint8_t pValue)
                                                   {
                                                     // Perform DMA operation
                                                     int source = static_cast<int>(pValue) << 8;
                                                     this->mSrc = source;
                                                     this->mPos = 0;
                                                     // TODO: Lock memory
                                                   }));
}

void gb_system::dma::tick()
{
  if (this->mPos >= 0)
  {
    auto &memory = *(this->mSystem.mMemoryBus);
    auto value = memory.read(this->mSrc + this->mPos);
    memory.write(0xfe00 + this->mPos, value);
    this->mPos += 1;
    if (this->mPos >= 160)
    {
      this->mPos = -1;
      // TODO: Unlock memory
    }
  }
}
