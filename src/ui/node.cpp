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

bool ui::node::contains(const std::shared_ptr<node> &pNode)
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
  std::shared_ptr<node> target = std::make_shared<node>();
  // FIXME: Copy attributes, etc
  for (auto iter = this->mChildren.begin(); iter != this->mChildren.end(); iter++)
  {
    target->append_child((*iter)->clone_node());
  }
  return target;
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

std::optional<std::string> ui::node::get_attribute(const std::string &pName)
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

bool ui::node::has_attribute(const std::string &pName)
{
  return this->mAttributes.contains(pName);
}

std::unordered_map<std::string, std::string> &ui::node::attributes()
{
  return this->mAttributes;
}

ui::node_type ui::node::node_type()
{
  return this->mNodeType;
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
