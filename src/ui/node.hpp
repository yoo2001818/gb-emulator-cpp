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
  enum node_type
  {
    element,
    text,
  };
  class node : public std::enable_shared_from_this<node>
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

    node_type node_type();

  private:
    std::weak_ptr<node> mParentNode;
    std::vector<std::shared_ptr<node>> mChildren;
    std::unordered_map<std::string, std::string> mAttributes;
    ui::node_type mNodeType = node_type::element;

    void _query_selector_all_impl(const ui::query_selector &pSelector, std::vector<std::shared_ptr<node>> &pList);
    void _update_parent(node *pNode);
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
  enum node_type
  {
    text,
    button
  };
  class document
  {
    std::shared_ptr<node> create_element(node_type pType);
  };
}

#endif // __NODE_HPP__
