#include <catch2/catch.hpp>
#include <sstream>
#include "../src/ui/node.hpp"

TEST_CASE("Converts node hierarchy to string", "[node]")
{
  auto rootEl = std::make_shared<ui::element>("DIV");
  auto textEl = std::make_shared<ui::text>("Hello,");
  auto bEl = std::make_shared<ui::element>("B");
  auto text2El = std::make_shared<ui::text>("world!");

  rootEl->set_attribute("class", "msg");
  rootEl->append_child(textEl);
  rootEl->append_child(bEl);
  bEl->append_child(text2El);

  std::stringstream sstream;
  sstream << *rootEl;
  REQUIRE(sstream.str() == "<div class=\"msg\">Hello,<b>world!</b></div>");
}
