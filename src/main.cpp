#include "console.h"

void kitchen_sink()
{
  fun::console("A new line is printed by default.");
  fun::console("Emojis are supported: :musical note: Baby :shark:, do do "
               ":musical note:");
  fun::console("*Bold* and _italic_ markdown text is supported.");
}

int main()
{
  kitchen_sink();
  return 0;
}
