#include <cctype>
#include <algorithm>
#include "node.hpp"

void ui::node::append_child(const std::shared_ptr<node> &pNode)
{
  this->mChildren.push_back(pNode);
  pNode->_update_parent(this);
}

void ui::node::remove_child(const std::shared_ptr<node> &pNode)
{
  for (auto iter = this->mChildren.begin(); iter != this->mChildren.end(); iter++)
  {
    if (&(**iter) == &(*pNode))
    {
      this->mChildren.erase(iter);
      pNode->_update_parent(nullptr);
      break;
    }
  }
}

void ui::node::insert_before(const std::shared_ptr<node> &pNode, const std::shared_ptr<node> &pPosition)
{
  for (auto iter = this->mChildren.begin(); iter != this->mChildren.end(); iter++)
  {
    if (&(**iter) == &(*pNode))
    {
      this->mChildren.insert(iter, pNode);
      pNode->_update_parent(this);
      break;
    }
  }
}

bool ui::node::contains(const std::shared_ptr<node> &pNode) const
{
  for (auto iter = this->mChildren.begin(); iter != this->mChildren.end(); iter++)
  {
    if (&(**iter) == &(*pNode))
      return true;
    if ((*iter)->contains(pNode))
      return true;
  }
  return false;
}

std::shared_ptr<ui::node> ui::node::clone_node()
{
  // FIXME: Implement it properly; we don't have a way to initialize the node yet
  /*
  std::shared_ptr<node> target = std::make_shared<node>();
  // FIXME: Copy attributes, etc
  for (auto iter = this->mChildren.begin(); iter != this->mChildren.end(); iter++)
  {
    target->append_child((*iter)->clone_node());
  }
  return target;
  */
  return nullptr;
}

std::vector<std::shared_ptr<ui::node>> &ui::node::children()
{
  return this->mChildren;
}

std::shared_ptr<ui::node> ui::node::query_selector(const ui::query_selector &pSelector)
{
  for (auto iter = this->mChildren.begin(); iter != this->mChildren.end(); iter++)
  {
    // FIXME: Actually implement query selector
    auto result = (*iter)->query_selector(pSelector);
    if (result != nullptr)
      return result;
  }
  return nullptr;
}

std::vector<std::shared_ptr<ui::node>> ui::node::query_selector_all(const ui::query_selector &pSelector)
{
  std::vector<std::shared_ptr<ui::node>> list;
  this->_query_selector_all_impl(pSelector, list);
  return list;
}

void ui::node::_query_selector_all_impl(const ui::query_selector &pSelector, std::vector<std::shared_ptr<ui::node>> &pList)
{
  for (auto iter = this->mChildren.begin(); iter != this->mChildren.end(); iter++)
  {
    // FIXME: Actually implement query selector
    (*iter)->_query_selector_all_impl(pSelector, pList);
  }
}

std::optional<std::string> ui::node::get_attribute(const std::string &pName) const
{
  auto iter = this->mAttributes.find(pName);
  if (iter == this->mAttributes.end())
    return std::nullopt;
  return iter->second;
}

void ui::node::set_attribute(const std::string &pName, const std::string &pValue)
{
  this->mAttributes.insert_or_assign(pName, pValue);
}

bool ui::node::has_attribute(const std::string &pName) const
{
  return this->mAttributes.contains(pName);
}

const std::unordered_map<std::string, std::string> &ui::node::attributes() const
{
  return this->mAttributes;
}

const std::weak_ptr<ui::node> &ui::node::parent_node() const
{
  return this->mParentNode;
}

const ui::node_type &ui::node::node_type() const
{
  return this->mNodeType;
}

const std::string &ui::node::node_name() const
{
  return this->mNodeName;
}

void ui::node::_update_parent(node *pNode)
{
  if (pNode != nullptr)
  {
    this->mParentNode = pNode->weak_from_this();
  }
  else
  {
    this->mParentNode.reset();
  }
}

int ui::node::_calculate_size(const ui::length_unit &pUnit)
{
  switch (pUnit.type)
  {
  case ui::length_unit_type::UNITLESS:
    return 0;
  case ui::length_unit_type::PX:
    return pUnit.value;
  // FIXME: Other units require getting the whole context
  default:
    return 0;
  }
}

ui::element::element(const std::string &pTagName) : mTagName(pTagName)
{
  this->mNodeType = node_type::element;
  this->mNodeName = pTagName;
}

void ui::element::layout(layout_handle &pLayoutHandle)
{
}

void ui::element::render(render_handle &pRenderHandle)
{
  auto borderTop = this->_calculate_size(this->mStyle.border.top.width);
  auto borderLeft = this->_calculate_size(this->mStyle.border.left.width);
  auto borderRight = this->_calculate_size(this->mStyle.border.right.width);
  auto borderBottom = this->_calculate_size(this->mStyle.border.bottom.width);
  if (this->mStyle.background)
  {
    // FIXME: Assuming RGB
    auto color = this->mStyle.background->value.color;
    SDL_SetRenderDrawColor(pRenderHandle.mRenderer, color >> 16, color >> 8, color, SDL_ALPHA_OPAQUE);
    SDL_Rect rect{
        this->mOffsetBorderRect.x + borderLeft,
        this->mOffsetBorderRect.y + borderTop,
        this->mOffsetBorderRect.width - borderLeft - borderRight,
        this->mOffsetBorderRect.height - borderTop - borderBottom,
    };
    SDL_RenderFillRect(pRenderHandle.mRenderer, &rect);
  }
  for (auto iter = this->mChildren.begin(); iter != this->mChildren.end(); iter++)
  {
    (*iter)->render(pRenderHandle);
  }
  // Draw border, for each edge and vertex
  if (borderTop)
  {
    auto color = this->mStyle.border.top.color.value.color;
    SDL_SetRenderDrawColor(pRenderHandle.mRenderer, color >> 16, color >> 8, color, SDL_ALPHA_OPAQUE);
    SDL_Rect rect{
        this->mOffsetBorderRect.x + borderLeft,
        this->mOffsetBorderRect.y,
        this->mOffsetBorderRect.width - borderLeft,
        borderTop,
    };
    SDL_RenderFillRect(pRenderHandle.mRenderer, &rect);
  }
  if (borderRight)
  {
    auto color = this->mStyle.border.top.color.value.color;
    SDL_SetRenderDrawColor(pRenderHandle.mRenderer, color >> 16, color >> 8, color, SDL_ALPHA_OPAQUE);
    SDL_Rect rect{
        this->mOffsetBorderRect.x + this->mOffsetBorderRect.width,
        this->mOffsetBorderRect.y + borderTop,
        borderRight,
        this->mOffsetBorderRect.height - borderTop};
    SDL_RenderFillRect(pRenderHandle.mRenderer, &rect);
  }
  if (borderBottom)
  {
    auto color = this->mStyle.border.top.color.value.color;
    SDL_SetRenderDrawColor(pRenderHandle.mRenderer, color >> 16, color >> 8, color, SDL_ALPHA_OPAQUE);
    SDL_Rect rect{
        this->mOffsetBorderRect.x,
        this->mOffsetBorderRect.y + this->mOffsetBorderRect.height - borderBottom,
        this->mOffsetBorderRect.width - borderRight,
        borderBottom,
    };
    SDL_RenderFillRect(pRenderHandle.mRenderer, &rect);
  }
  if (borderLeft)
  {
    auto color = this->mStyle.border.top.color.value.color;
    SDL_SetRenderDrawColor(pRenderHandle.mRenderer, color >> 16, color >> 8, color, SDL_ALPHA_OPAQUE);
    SDL_Rect rect{
        this->mOffsetBorderRect.x,
        this->mOffsetBorderRect.y,
        borderLeft,
        this->mOffsetBorderRect.height - borderBottom};
    SDL_RenderFillRect(pRenderHandle.mRenderer, &rect);
  }
}

void ui::element::print(std::ostream &pWhere) const
{
  auto nodeName = this->mNodeName;
  std::transform(nodeName.begin(), nodeName.end(), nodeName.begin(), [](unsigned char c)
                 { return std::tolower(c); });
  pWhere << "<";
  pWhere << nodeName;

  for (auto iter = this->mAttributes.begin(); iter != this->mAttributes.end(); iter++)
  {
    pWhere << " ";
    pWhere << iter->first;
    pWhere << "=\"";
    pWhere << iter->second;
    pWhere << "\"";
  }

  pWhere << ">";

  for (auto iter = this->mChildren.begin(); iter != this->mChildren.end(); iter++)
  {
    pWhere << **iter;
  }

  pWhere << "</";
  pWhere << nodeName;
  pWhere << ">";
}

const std::string &ui::element::tag_name() const
{
  return this->mTagName;
}

ui::style &ui::element::style()
{
  return this->mStyle;
}

ui::text::text(const std::string &pData) : mData(pData)
{
  this->mNodeType = node_type::text;
  this->mNodeName = "#text";
}

void ui::text::layout(layout_handle &pLayoutHandle)
{
}

void ui::text::render(render_handle &pRenderHandle)
{
}

void ui::text::print(std::ostream &pWhere) const
{
  pWhere << this->mData;
}

const std::string &ui::text::data() const
{
  return this->mData;
}

void ui::text::data(const std::string &pData)
{
  this->mData = pData;
}

std::ostream &operator<<(std::ostream &out, const ui::node &pNode)
{
  pNode.print(out);
  return out;
}
