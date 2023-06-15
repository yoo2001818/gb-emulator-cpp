#include "component.hpp"

#ifndef __DMA_HPP__
#define __DMA_HPP__

namespace gb_system
{
  class system;
  class dma : public component
  {
  public:
    int mSrc;
    int mPos = -1;
    dma(system &pSystem) : mSystem(pSystem){};
    void reset();
    void register_system();
    void tick();

  private:
    system &mSystem;
  };
}

#endif // __DMA_HPP__
