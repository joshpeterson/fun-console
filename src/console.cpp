#include "console.h"

#include <cstdio>

namespace easy
{
void console(const char* message)
{
  static Console console;
  printf("%s", console.Format(message).c_str());
}

std::string Console::Format(const std::string& message)
{
  return AddNewLine(ReplaceEmoji(message));
}

std::string Console::AddNewLine(const std::string& message)
{
  return message + "\n";
}

static bool found(std::string::size_type location)
{
  return location != std::string::npos;
}

std::string Console::ReplaceEmoji(const std::string& message)
{
  std::string shark = ":shark:";
  auto location = message.find(shark);
  if (!found(location))
    return message;

  std::string result = message;
  while (found(location))
  {
    result.replace(location, shark.length(), u8"\U0001F988");
    location = result.find(shark);
  }
  return result;
}

} // namespace easy
