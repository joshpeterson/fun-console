#include "console.h"
#include "emoji.h"
#include "platform-factory.h"

#include <cstdio>
#include <unordered_map>

namespace easy
{

void console(const char* message)
{
  static Console console;
  printf("%s", console.Format(message).c_str());
}

Console::Console() : Console(PlatformFactory::Current()) {}

Console::Console(const Platform* platform) : platform_(platform) {}

std::string Console::Format(const std::string& message)
{
  auto afterEmoji = message;
  if (platform_->SupportsEmoji())
    afterEmoji = Emoji::Replace(message);
  return AddNewLine(afterEmoji);
}

std::string Console::AddNewLine(const std::string& message)
{
  return message + "\n";
}

} // namespace easy
