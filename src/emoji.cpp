#include "emoji.h"
#include "emoji-data.h"

#include <unordered_map>

namespace fun
{

static bool found(std::unordered_map<std::string, std::string>::iterator emoji)
{
  return emoji != emojis.end();
}

static bool tryGetEmoji(const std::string& emoji, std::string& unicodeValue)
{
  auto possibleEmoji = emojis.find(emoji);
  if (!found(possibleEmoji))
    return false;

  unicodeValue = possibleEmoji->second;
  return true;
}

static bool found(std::string::size_type location)
{
  return location != std::string::npos;
}

std::string Emoji::Replace(const std::string& message)
{
  auto emojiStart = message.find_first_of(':');
  if (!found(emojiStart))
    return message;

  auto emojiEnd = message.find_first_of(':', emojiStart + 1);
  if (!found(emojiEnd))
    return message;

  std::string result = message;
  while (found(emojiEnd))
  {
    // Extract the emoji from the larger string
    auto emoji = result.substr(emojiStart + 1, emojiEnd - emojiStart - 1);

    std::string unicodeValue;
    if (tryGetEmoji(emoji, unicodeValue))
    {
      // Replace the emoji plus the leading the trailing colons
      result.replace(emojiStart, emoji.length() + 2, unicodeValue);

      // Look for the next emoji
      emojiStart = result.find_first_of(':');
    }
    else
    {
      // This was not an emoji, so start looking for the next one after it
      emojiStart = result.find_first_of(':', emojiStart + 1);
    }

    if (!found(emojiStart))
      return result;
    emojiEnd = result.find_first_of(':', emojiStart + 1);
  }

  return result;
}

} // namespace fun
