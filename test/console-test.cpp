#include "catch.hpp"

#include "console.h"
#include "platform.h"

using namespace fun;

TEST_CASE("Console with emoji support")
{
  class PlatformWithEmoji : public Platform
  {
  public:
    bool SupportsEmoji() const override { return true; }
  };
  Console console(new PlatformWithEmoji());

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

TEST_CASE("Console without emoji support")
{
  class PlatformWithoutEmoji : public Platform
  {
  public:
    bool SupportsEmoji() const override { return false; }
  };

  Console console(new PlatformWithoutEmoji());

  SECTION("Format does not replace emojis")
  {
    REQUIRE(
        console.Format(":musical note: Baby :shark:, do do :musical note:") ==
        ":musical note: Baby :shark:, do do :musical note:\n");
  }
}

TEST_CASE("Console with control character support")
{
  class PlatformWithControlCharacters : public Platform
  {
  public:
    bool SupportsControlCharacters() const override { return true; }
  };
  Console console(new PlatformWithControlCharacters());

  SECTION("Format replaces bold markdown")
  {
    REQUIRE(console.Format("*bold* text") == "\033[1mbold\033[0m text\n");
  }
}

TEST_CASE("Console without control character support")
{
  class PlatformWithoutControlCharacters : public Platform
  {
  public:
    bool SupportsControlCharacters() const override { return false; }
  };
  Console console(new PlatformWithoutControlCharacters());

  SECTION("Format does not replaces markdown")
  {
    REQUIRE(console.Format("*bold* text") == "*bold* text\n");
  }
}
