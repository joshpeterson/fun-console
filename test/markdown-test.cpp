#include "catch.hpp"

#include "markdown.h"

using namespace fun;

TEST_CASE("Markdown")
{
  SECTION("Don't change a string with no markdown")
  {
    REQUIRE(Markdown::Replace("has no markdown") == "has no markdown");
  }

  SECTION("Can parse bold markers from a string")
  {
    REQUIRE(Markdown::Replace("*bold* text") == "\033[1mbold\033[0m text");
  }

  SECTION("Can parse two bold markers from a string")
  {
    REQUIRE(Markdown::Replace("*bold* text *again*") ==
            "\033[1mbold\033[0m text \033[1magain\033[0m");
  }

  SECTION("Treats two consecutive bold markers as one")
  {
    REQUIRE(Markdown::Replace("**bold** text") == "\033[1mbold\033[0m text");
  }

  SECTION("Treats two consecutive bold markers as one twice")
  {
    REQUIRE(Markdown::Replace("**bold** text **again**") ==
            "\033[1mbold\033[0m text \033[1magain\033[0m");
  }

  SECTION("Can escape bold markers from a string")
  {
    REQUIRE(Markdown::Replace("\\*not bold\\* text") == "\\*not bold\\* text");
  }

  SECTION("Ignores bold markers surrounded by spaces")
  {
    REQUIRE(Markdown::Replace(" * not bold * text") == " * not bold * text");
  }

  SECTION("Can parse italic markers from a string")
  {
    REQUIRE(Markdown::Replace("_italic_ text") == "\033[3mitalic\033[0m text");
  }

  SECTION("Can parse two talic markers from a string")
  {
    REQUIRE(Markdown::Replace("_italic_ text _again_") ==
            "\033[3mitalic\033[0m text \033[3magain\033[0m");
  }

  SECTION("Treats two consecutive italic markers as one")
  {
    REQUIRE(Markdown::Replace("__italic__ text") ==
            "\033[3mitalic\033[0m text");
  }

  SECTION("Treats two consecutive italic markers as one twice")
  {
    REQUIRE(Markdown::Replace("__italic__ text __again__") ==
            "\033[3mitalic\033[0m text \033[3magain\033[0m");
  }

  SECTION("Can escape italic markers from a string")
  {
    REQUIRE(Markdown::Replace("\\_not italic\\_ text") ==
            "\\_not italic\\_ text");
  }

  SECTION("Ignores italic markers surrounded by spaces")
  {
    REQUIRE(Markdown::Replace(" _ not italic _ text") ==
            " _ not italic _ text");
  }
}
