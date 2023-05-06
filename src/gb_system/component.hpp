#ifndef __COMPONENT_HPP__
#define __COMPONENT_HPP__

namespace gb_system
{
  class component
  {
  public:
    virtual ~component() {};
    virtual void reset() = 0;
    virtual void register_system() = 0;
    virtual void tick(int pTicks) = 0;
  };
}

#endif // __COMPONENT_HPP__
