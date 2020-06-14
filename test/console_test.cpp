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
    REQUIRE(console.Format("Baby :shark:") == u8"Baby \U0001F988\n");
  }

  SECTION("AddNewLine adds a newline to the end of the message")
  {
    REQUIRE(console.AddNewLine("It was the best") == "It was the best\n");
  }

  SECTION("ReplaceEmoji does nothing when no emojis are found")
  {
    REQUIRE(console.ReplaceEmoji("Baby shark") == "Baby shark");
  }

  SECTION("ReplaceEmoji replaces the :shark:")
  {
    REQUIRE(console.ReplaceEmoji("Baby :shark:, do do") ==
            u8"Baby \U0001F988, do do");
  }

  SECTION("ReplaceEmoji replaces the more than one emoji string")
  {
    REQUIRE(console.ReplaceEmoji("Baby :shark: :shark: :shark:") ==
            u8"Baby \U0001F988 \U0001F988 \U0001F988");
  }
}
