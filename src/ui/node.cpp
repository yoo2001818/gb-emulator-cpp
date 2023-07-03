#include "node.hpp"

void ui::node::append_child(const std::shared_ptr<node> &pNode)
{
  this->mChildren.push_back(pNode);
}

void ui::node::remove_child(const std::shared_ptr<node> &pNode)
{
  for (auto iter = this->mChildren.begin(); iter != this->mChildren.end(); iter++)
  {
    if (&(**iter) == &(*pNode))
    {
      this->mChildren.erase(iter);
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
