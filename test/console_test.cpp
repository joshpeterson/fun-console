#include "catch.hpp"

#include "console.h"

using namespace easy;

TEST_CASE("Console")
{
  Console console;

  SECTION("Format adds a newline to the end of the message")
  {
    REQUIRE(console.Format("It was the best") == "It was the best\n");
  }

  SECTION("Format replaces emojis")
  {
    REQUIRE(
        console.Format(":musical note: Baby :shark:, do do :musical note:") ==
        u8"\U0001F3B5 Baby \U0001F988, do do \U0001F3B5\n");
  }

  SECTION("AddNewLine adds a newline to the end of the message")
  {
    REQUIRE(console.AddNewLine("It was the best") == "It was the best\n");
  }
}
