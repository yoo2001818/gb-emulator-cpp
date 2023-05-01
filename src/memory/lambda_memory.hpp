#include <functional>
#include "memory.hpp"

#ifndef __LAMBDA_MEMORY_HPP__
#define __LAMBDA_MEMORY_HPP__

using namespace std;

namespace memory
{
  class lambda_memory : public memory
  {
  public:
    function<uint8_t(uint16_t)> mReadFn;
    function<void(uint16_t, uint8_t)> mWriteFn;
    lambda_memory(function<uint8_t(uint16_t)> pReadFn, function<void(uint16_t, uint8_t)> pWriteFn) :
      mReadFn(pReadFn), mWriteFn(pWriteFn) {}
    virtual uint8_t read(uint16_t pAddr);
    virtual void write(uint16_t pAddr, uint8_t pValue);
    virtual void reset();
  };
};

#endif // __LAMBDA_MEMORY_HPP__
