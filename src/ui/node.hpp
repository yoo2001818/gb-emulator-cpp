#include <memory>
#include <vector>
#include <optional>
#include <unordered_map>
#include <ostream>

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
  enum class node_type
  {
    element,
    text,
  };
  class node : public std::enable_shared_from_this<node>
  {
  public:
    node(){};
    virtual ~node(){};
    // virtual void layout() = 0;
    // virtual void render(render_handle &mRenderHandle) = 0;
    virtual void print(std::ostream &where) const = 0;

    void append_child(const std::shared_ptr<node> &pNode);
    void remove_child(const std::shared_ptr<node> &pNode);
    void insert_before(const std::shared_ptr<node> &pNode, const std::shared_ptr<node> &pPosition);
    bool contains(const std::shared_ptr<node> &pNode) const;
    std::shared_ptr<node> clone_node();
    std::vector<std::shared_ptr<node>> &children();
    std::shared_ptr<node> query_selector(const query_selector &pSelector);
    std::vector<std::shared_ptr<node>> query_selector_all(const ui::query_selector &pSelector);

    std::optional<std::string> get_attribute(const std::string &pName) const;
    void set_attribute(const std::string &pName, const std::string &pValue);
    bool has_attribute(const std::string &pName) const;
    const std::unordered_map<std::string, std::string> &attributes() const;

    const std::weak_ptr<node> &parent_node() const;

    const ui::node_type &node_type() const;
    const std::string &node_name() const;

  protected:
    std::weak_ptr<node> mParentNode;
    std::vector<std::shared_ptr<node>> mChildren;
    std::unordered_map<std::string, std::string> mAttributes;
    ui::node_type mNodeType = node_type::element;
    std::string mNodeName;

    void _query_selector_all_impl(const ui::query_selector &pSelector, std::vector<std::shared_ptr<node>> &pList);
    void _update_parent(node *pNode);
  };
  class element : public node
  {
  public:
    element(const std::string &pTagName);
    virtual void print(std::ostream &pWhere) const;

    const std::string &tag_name() const;

  protected:
    std::string mTagName;
  };
  class text : public node
  {
  public:
    text(const std::string &pData);
    virtual void print(std::ostream &pWhere) const;

    const std::string &data() const;
    void data(const std::string &pData);

  protected:
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
  enum class element_type
  {
    text,
    button
  };
  class document
  {
    std::shared_ptr<node> create_element(element_type pType);
  };
}

std::ostream &operator<<(std::ostream &out, const ui::node &pNode);

#endif // __NODE_HPP__
