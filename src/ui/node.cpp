#include "node.hpp"

void ui::element::addChild(std::shared_ptr<node> pNode)
{
  this->mChildren.push_back(pNode);
}

void ui::element::removeChild(std::shared_ptr<node> pNode)
{
  auto iter = this->mChildren.begin();
  while (iter != this->mChildren.end())
  {
    if (&(**iter) == &(*pNode))
    {
      this->mChildren.erase(iter);
      break;
    }
    iter++;
  }
}

std::vector<std::shared_ptr<ui::node>> &ui::element::children()
{
  return this->mChildren;
}
