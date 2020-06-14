#include "console.h"

void kitchen_sink()
{
  easy::console("A new line is printed by default");
  easy::console("Emojis are supported: :shark:");
}

int main()
{
  kitchen_sink();
  return 0;
}
