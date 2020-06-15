#include "console.h"

void kitchen_sink()
{
  easy::console("A new line is printed by default");
  easy::console("Emojis are supported: :musical note: Baby :shark:, do do "
                ":musical note:");
}

int main()
{
  kitchen_sink();
  return 0;
}
