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
  enum class length_unit_type
  {
    CH,
    EM,
    EX,
    IC,
    LH,
    REM,
    RLH,
    VH,
    VW,
    VMAX,
    VMIN,
    VB,
    VI,
    PX,
    CM,
    MM,
    Q,
    IN,
    PC,
    PT,
    PERCENTAGE,
    UNITLESS
  };
  class length_unit
  {
  public:
    length_unit_type type;
    float value;
  };
  class length_auto_unit
  {
  public:
    enum
    {
      AUTO,
      LENGTH
    } type;
    union
    {
      length_unit_type length;
    } value;
  };
  class color_value
  {
  public:
    enum
    {
      RGB,
      RGBA,
      CURRENT_COLOR
    } type;
    union
    {
      int color;
    } value;
  };
  class style_box
  {
  public:
    length_auto_unit top;
    length_auto_unit left;
    length_auto_unit right;
    length_auto_unit bottom;
  };
  enum class border_style
  {
    NONE,
    HIDDEN,
    DOTTED,
    DASHED,
    SOLID,
    DOUBLE,
    GROOVE,
    RIDGE,
    INSET,
    OUTSET,
  };
  class style_border
  {
  public:
    length_unit width;
    border_style style;
    color_value color;
  };
  class style_border_box
  {
  public:
    style_border top;
    style_border left;
    style_border right;
    style_border bottom;
  };
  enum class display_value
  {
    BLOCK,
    INLINE_BLOCK,
    INLINE,
    NONE
  };
  enum class visibility_value
  {
    VISIBLE,
    HIDDEN,
  };
  enum class position_value
  {
    STATIC,
    RELATIVE,
    ABSOLUTE,
    FIXED,
    STICKY
  };
  class z_index_value
  {
  public:
    enum
    {
      AUTO,
      VALUE
    } type;
    int value;
  };
  enum class overflow_value
  {
    VISIBLE,
    HIDDEN,
    SCROLL
  };
  enum class white_space_value
  {
    NORMAL,
    NOWRAP,
    PRE,
    PRE_WRAP,
    PRE_LINE,
    BREAK_SPACES
  };
  class style_font
  {
  public:
    length_unit size;
    length_unit lineHeight;
  };
  class style : public style_box
  {
  public:
    style_box margin;
    style_box padding;
    style_border_box border;
    // No image background is supported for now...
    std::optional<color_value> background;
    display_value display;
    visibility_value visibility;
    position_value position;
    z_index_value zIndex;
    length_auto_unit width;
    length_auto_unit height;
    std::optional<length_auto_unit> minWidth;
    std::optional<length_auto_unit> minHeight;
    std::optional<length_auto_unit> maxWidth;
    std::optional<length_auto_unit> maxHeight;
    overflow_value overflow;
    color_value color;
    white_space_value whiteSpace;
    style_font font;
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
    text
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

    virtual const rect &offset_rect();

  protected:
    std::weak_ptr<node> mParentNode;
    std::vector<std::shared_ptr<node>> mChildren;
    std::unordered_map<std::string, std::string> mAttributes;
    ui::node_type mNodeType = node_type::element;
    std::string mNodeName;

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
