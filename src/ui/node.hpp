#include <memory>
#include <vector>
#include <optional>
#include <unordered_map>
#include <ostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include "style.hpp"
#include "../app/font_renderer.hpp"

#ifndef __NODE_HPP__
#define __NODE_HPP__

// # Positioning and bounds
// Like HTML / CSS (and unlike other traditional layout engines), this
// should support various features properties that CSS implements -
// Including inline, box, flex formatting context, margin/padding/border,
// overflows, etc.
//
// This is simply to learn about how web browsers render HTML documents -
// I would've been using imgui if I wanted to build UI quickly - so I
// actually don't have reasoning for this.
//
// But, anyway, this decision have many consequences, and one thing is that
// a single element can't be rendered using a single rectangle. Their
// children could be flying all over the place, and the element itself can
// be defined using multiple rectangles - this is the case for inline and
// list-item, etc.
//
// Particularly, the inline formatting context is very troublesome to
// implement.
//
// To support all of the CSS-esque features, the element should contain
// the following:
//
// - The "offset" parent
// - The rectangles according to the offset
//
// Using the information, the element itself places their children (sets
// the position info directly). However the rectangle itself should be
// negotiated by the child as well.
//
// ## Layout
// For the case of block formatting context (we omit float for the sake of
// simplicity), it's really simple enough - the container has fixed width
// and the children gets the fixed width as well. Since everything is
// predictable from the start, we can retrieve each child's required height
// and lay them out as we go.
//
// Inline is however quite complicated; but in a nutshell, each word can be
// broken up to separate lines, and we have to determine and lay the words
// out in multiple lines, while keeping in mind of the line height.
// This means that each word, or inline-block element's width should be
// calculate beforehand, unlike block formatting context.
//
// To generalize everything, we do the following:
// - Each element, including text, can calculate "preferred width"
// - Only inline formatting context uses "preferred width" for now
// - Text processing is delegated to the element, which handles inline
//   formatting context by itself, after collecting all text and elements
// - We need to build another tree model for handling pseudo elements,
//   auto-generated elements, etc
// - Layout process is usually done in one inorder traversal - except for
//   elements that requires calculating preferred width, which involves
//   simulating the layout process
// - To avoid any confusion, we explicitly have to tell which variable uses
//   which box in the box model - e.g. content-box, border-box, padding-box
// - Margins are handled by the parent's layout model - it is completely
//   ignored by the element itself
// - The element itself only draws background, border, etc
//
// Implementing this is a big concern though; It's hard to model this into
// relevant structures.

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
  class render_handle
  {
  public:
    SDL_Renderer *mRenderer;
    SDL_Texture *mRootTexture;
    // TODO: Elements with overflow (or new layer) should make their own
    // texture and manage it
    app::font_renderer *mFontRenderer;
  };
  class layout_handle
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
    text
  };
  class node : public std::enable_shared_from_this<node>
  {
  public:
    node(){};
    virtual ~node(){};
    virtual void layout(layout_handle &pLayoutHandle) = 0;
    virtual void render(render_handle &pRenderHandle) = 0;
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
    // FIXME: If overflow and transform is implemented, this should point the
    // offset parent, preferably using weak_ptr
    void *mOffsetParent;
    ui::rect mOffsetBorderRect;

    void _query_selector_all_impl(const ui::query_selector &pSelector, std::vector<std::shared_ptr<node>> &pList);
    void _update_parent(node *pNode);
    int _calculate_size(const ui::length_unit &pUnit);
  };
  class element : public node
  {
  public:
    element(const std::string &pTagName);
    virtual void layout(layout_handle &pLayoutHandle);
    virtual void render(render_handle &pRenderHandle);
    virtual void print(std::ostream &pWhere) const;

    const std::string &tag_name() const;
    ui::style &style();

  protected:
    std::string mTagName;
    ui::style mStyle;
  };
  class text : public node
  {
  public:
    text(const std::string &pData);
    virtual void layout(layout_handle &pLayoutHandle);
    virtual void render(render_handle &pRenderHandle);
    virtual void print(std::ostream &pWhere) const;

    const std::string &data() const;
    void data(const std::string &pData);

  protected:
    std::string mData;
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
