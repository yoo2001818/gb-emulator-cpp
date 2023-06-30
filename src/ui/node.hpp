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
    int width;
  };
  class render_handle;
  class node
  {
  public:
    node(){};
    virtual ~node(){};
    virtual void layout() = 0;
    virtual void render(render_handle &mRenderHandle) = 0;

  private:
    std::weak_ptr<node> mParent;
    rect mBoundingRect;
    style mStyle;
  };
  class layout_node
  {
  public:
    layout_node(){};
    virtual ~layout_node(){};
  };
  class element : public node
  {
  public:
    element(){};
    virtual ~element(){};
    virtual void layout() = 0;
    virtual void render(render_handle &mRenderHandle) = 0;

    void add_child(std::shared_ptr<node> pNode);
    void remove_child(std::shared_ptr<node> pNode);
    std::vector<std::shared_ptr<node>> &children();

  private:
    std::vector<layout_node> mPreNodes;
    std::vector<layout_node> mPostNodes;
    std::vector<std::shared_ptr<node>> mChildren;
  };
  class text : public node
  {
  private:
    std::string mData;
  };
  class button : public element
  {
  };
  class v_stack : public element
  {
  };
  class body : public element
  {
  };
  enum element_type
  {
    text,
    button
  };
  class document
  {
    std::shared_ptr<node> create_element(element_type pType);
  };
}

#endif // __NODE_HPP__
