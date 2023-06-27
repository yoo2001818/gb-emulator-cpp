#include <memory>
#include <vector>

#ifndef __NODE_HPP__
#define __NODE_HPP__

namespace ui
{
  class rect
  {
  public:
    int x;
    int y;
    int width;
    int height;
  };
  class style
  {
  public:
    };
  class render_handle;
  class node
  {
  public:
    node();
    virtual ~node();
    virtual void layout() = 0;
    virtual void render(render_handle &mRenderHandle) = 0;

  private:
    std::weak_ptr<node> mParent;
    std::vector<rect> mSubRects;
    rect mRect;
  };
  class element : public node
  {
  public:
    element();
    virtual ~element();
    virtual void layout() = 0;
    virtual void render(render_handle &mRenderHandle) = 0;

    void addChild(std::shared_ptr<node> pNode);
    void removeChild(std::shared_ptr<node> pNode);
    std::vector<std::shared_ptr<node>> &children();

  private:
    std::vector<std::shared_ptr<node>> mChildren;
  };
  class text : public node
  {
  };
  class button : public element
  {
  };
  class v_stack : public element
  {
  };
}

#endif // __NODE_HPP__
