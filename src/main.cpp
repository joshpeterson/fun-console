#include "console.h"

void kitchenSink()
{
  fun::console("A new line is printed by default.");
  fun::console("Emojis are supported: :musical note: Baby :shark:, do do "
               ":musical note:");
  fun::console("*Bold* and _italic_ markdown text is supported.");
  fun::console("And "
               "[red]c[/red][cyan]o[/cyan][yellow]l[/yellow][green]o[/"
               "green][blue]r[/blue][magenta]s[/magenta]!");
}

int main()
{
  kitchenSink();
  return 0;
}
