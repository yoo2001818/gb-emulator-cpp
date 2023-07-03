#include <memory>
#include <vector>
#include <optional>
#include <unordered_map>

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
  class render_handle
  {
  public:
    int dummy;
  };
  class query_selector
  {
  public:
    std::string class_name;
  };
  class node
  {
  public:
    node(){};
    virtual ~node(){};
    virtual void layout() = 0;
    virtual void render(render_handle &mRenderHandle) = 0;

    void append_child(const std::shared_ptr<node> &pNode);
    void remove_child(const std::shared_ptr<node> &pNode);
    void insert_before(const std::shared_ptr<node> &pNode, const std::shared_ptr<node> &pPosition);
    bool contains(const std::shared_ptr<node> &pNode);
    std::shared_ptr<node> clone_node();
    std::vector<std::shared_ptr<node>> &children();
    std::shared_ptr<node> query_selector(const query_selector &pSelector);
    std::vector<std::shared_ptr<node>> query_selector_all(const ui::query_selector &pSelector);

    std::optional<std::string> get_attribute(const std::string &pName);
    void set_attribute(const std::string &pName, const std::string &pValue);
    bool has_attribute(const std::string &pName);
    std::unordered_map<std::string, std::string> &attributes();

  private:
    std::weak_ptr<node> mParent;
    std::vector<std::shared_ptr<node>> mChildren;
    std::unordered_map<std::string, std::string> mAttributes;

    void _query_selector_all_impl(const ui::query_selector &pSelector, std::vector<std::shared_ptr<node>> &pList);
  };
  class text : public node
  {
  private:
    std::string mData;
  };
  class button : public node
  {
  };
  class v_stack : public node
  {
  };
  class body : public node
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
