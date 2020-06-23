#include "catch.hpp"

#include "emoji.h"

using namespace fun;

TEST_CASE("Emoji")
{
  SECTION("ReplaceEmoji does nothing when no emojis are found")
  {
    REQUIRE(Emoji::Replace("Baby shark") == "Baby shark");
  }

  SECTION("ReplaceEmoji does not replace a non-emoji")
  {
    REQUIRE(Emoji::Replace("Not :an-emoji:") == "Not :an-emoji:");
  }

  SECTION("ReplaceEmoji replaces the :shark:")
  {
    REQUIRE(Emoji::Replace("Baby :shark:, do do") ==
            u8"Baby \U0001F988, do do");
  }

  SECTION("ReplaceEmoji replaces the :musical note:")
  {
    REQUIRE(Emoji::Replace(":musical note:") == u8"\U0001F3B5");
  }

  SECTION("ReplaceEmoji replaces the more than one emoji string")
  {
    REQUIRE(Emoji::Replace("Baby :shark: :shark: :shark:") ==
            u8"Baby \U0001F988 \U0001F988 \U0001F988");
  }

  SECTION("ReplaceEmoji replaces the :shark: after a non-emoji")
  {
    REQUIRE(Emoji::Replace(":not-an-emoji: Baby :shark:, do do") ==
            u8":not-an-emoji: Baby \U0001F988, do do");
  }

  SECTION("ReplaceEmoji skips a colon that is not part of an emoji")
  {
    REQUIRE(Emoji::Replace("Note: :musical note:") == u8"Note: \U0001F3B5");
  }
}
