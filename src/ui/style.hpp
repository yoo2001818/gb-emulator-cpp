#include <memory>
#include <vector>
#include <optional>

#ifndef __STYLE_HPP__
#define __STYLE_HPP__

namespace ui
{
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
    UNITLESS,
    AUTO
  };
  class length_unit
  {
  public:
    length_unit_type type;
    float value;
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
    length_unit top = {length_unit_type::AUTO, 0};
    length_unit left = {length_unit_type::AUTO, 0};
    length_unit right = {length_unit_type::AUTO, 0};
    length_unit bottom = {length_unit_type::AUTO, 0};
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
    length_unit width = {length_unit_type::UNITLESS, 0};
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
    style_box margin = {
        {length_unit_type::UNITLESS, 0},
        {length_unit_type::UNITLESS, 0},
        {length_unit_type::UNITLESS, 0},
        {length_unit_type::UNITLESS, 0}};
    style_box padding = {
        {length_unit_type::UNITLESS, 0},
        {length_unit_type::UNITLESS, 0},
        {length_unit_type::UNITLESS, 0},
        {length_unit_type::UNITLESS, 0}};
    style_border_box border;
    // No image background is supported for now...
    std::optional<color_value> background;
    display_value display = display_value::BLOCK;
    visibility_value visibility;
    position_value position;
    z_index_value zIndex;
    length_unit width = {length_unit_type::AUTO, 0};
    length_unit height = {length_unit_type::AUTO, 0};
    std::optional<length_unit> minWidth;
    std::optional<length_unit> minHeight;
    std::optional<length_unit> maxWidth;
    std::optional<length_unit> maxHeight;
    overflow_value overflow;
    color_value color;
    white_space_value whiteSpace;
    style_font font;
  };
}

#endif // __STYLE_HPP__
