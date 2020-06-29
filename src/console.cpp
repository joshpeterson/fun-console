#include "console.h"
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

Console::Console() : Console(PlatformFactory::Current()) {}

Console::Console(const Platform* platform) : platform_(platform) {}

std::string Console::Format(const std::string& message)
{
  auto afterEmoji = message;
  if (platform_->SupportsEmoji())
    afterEmoji = Emoji::Replace(message);

  auto afterControlCharacters = afterEmoji;
  if (platform_->SupportsControlCharacters())
    afterControlCharacters = Markdown::Replace(afterEmoji);
  return AddNewLine(afterControlCharacters);
}

std::string Console::AddNewLine(const std::string& message)
{
  return message + "\n";
}

} // namespace fun
