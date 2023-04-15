#ifndef __OP_HPP__
#define __OP_HPP__

namespace cpu
{
  namespace op 
  {
    class op {
    public:
      void exec() {};
    };
    class ld : op {
    };
  };
};

#endif // __OP_HPP__
