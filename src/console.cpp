#include "console.h"
#include "colors.h"
#include "emoji.h"
#include "markdown.h"
#include "platform-factory.h"

#include <cstdio>
#include <unordered_map>

namespace fun
{

void console(const char* message)
{
  static Console console;
  printf("%s", console.Format(message).c_str());
}

void console(const std::string& message) { console(message.c_str()); }

Console::Console() : Console(PlatformFactory::Current()) {}

Console::Console(const Platform* platform) : platform_(platform) {}

std::string Console::Format(const std::string& message)
{
  auto result = message;
  if (platform_->SupportsEmoji())
    result = Emoji::Replace(result);

  if (platform_->SupportsControlCharacters())
  {
    result = Markdown::Replace(result);
    result = Colors::Replace(result);
  }
  return AddNewLine(result);
}

std::string Console::AddNewLine(const std::string& message)
{
  return message + "\n";
}

} // namespace fun
