#include "console.h"
#include "emoji.h"

#include <cstdio>
#include <unordered_map>

namespace easy
{

void console(const char* message)
{
  static Console console;
  printf("%s", console.Format(message).c_str());
}

std::string Console::Format(const std::string& message)
{
  return AddNewLine(Emoji::Replace(message));
}

std::string Console::AddNewLine(const std::string& message)
{
  return message + "\n";
}

} // namespace easy
