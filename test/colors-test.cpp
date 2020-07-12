#include "catch.hpp"

#include "colors.h"

using namespace fun;

TEST_CASE("Colors")
{
  SECTION("Returns the input string when no colors are present")
  {
    REQUIRE(Colors::Replace("No colors here") == "No colors here");
  }

  SECTION("Replaces a color in square brackets")
  {
    REQUIRE(Colors::Replace("This is [red]red[/red]") ==
            "This is \033[31mred\033[0m");
  }

  SECTION("Replaces a different color in square brackets")
  {
    REQUIRE(Colors::Replace("This is [blue]blue[/blue]") ==
            "This is \033[34mblue\033[0m");
  }

  SECTION("Replaces a color with a space")
  {
    REQUIRE(
        Colors::Replace("This is [bright green]bright green[/bright green]") ==
        "This is \033[92mbright green\033[0m");
  }

  SECTION("Replaces two colors")
  {
    REQUIRE(
        Colors::Replace("First [red]red[/red] then [blue]blue[/blue] next") ==
        "First \033[31mred\033[0m then \033[34mblue\033[0m next");
  }

  SECTION("Skips a non-color in square brackets")
  {
    REQUIRE(Colors::Replace("This is [foo]red[/foo]") ==
            "This is [foo]red[/foo]");
  }

  SECTION("Skips mismatched colors")
  {
    REQUIRE(Colors::Replace("This is [red]red[/blue]") ==
            "This is [red]red[/blue]");
  }

  SECTION("Replaces one character colors")
  {
    REQUIRE(Colors::Replace("[red]c[/red][cyan]o[/cyan][yellow]l[/yellow]") ==
            "\033[31mc\033[0m\033[36mo\033[0m\033[33ml\033[0m");
  }
}
