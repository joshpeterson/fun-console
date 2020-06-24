#include "emoji.h"
#include "emoji-data.h"

#include <unordered_map>

namespace fun
{

static bool found(std::unordered_map<std::string, std::string>::iterator emoji)
{
  return emoji != emojis.end();
}

static bool try_get_emoji(const std::string& emoji, std::string& unicode_value)
{
  auto possible_emoji = emojis.find(emoji);
  if (!found(possible_emoji))
    return false;

  unicode_value = possible_emoji->second;
  return true;
}

static bool found(std::string::size_type location)
{
  return location != std::string::npos;
}

std::string Emoji::Replace(const std::string& message)
{
  auto emoji_start = message.find_first_of(':');
  if (!found(emoji_start))
    return message;

  auto emoji_end = message.find_first_of(':', emoji_start + 1);
  if (!found(emoji_end))
    return message;

  std::string result = message;
  while (found(emoji_end))
  {
    // Extract the emoji from the larger string
    auto emoji = result.substr(emoji_start + 1, emoji_end - emoji_start - 1);

    std::string unicode_value;
    if (try_get_emoji(emoji, unicode_value))
    {
      // Replace the emoji plus the leading the trailing colons
      result.replace(emoji_start, emoji.length() + 2, unicode_value);

      // Look for the next emoji
      emoji_start = result.find_first_of(':');
    }
    else
    {
      // This was not an emoji, so start looking for the next one after it
      emoji_start = result.find_first_of(':', emoji_start + 1);
    }

    if (!found(emoji_start))
      return result;
    emoji_end = result.find_first_of(':', emoji_start + 1);
  }

  return result;
}

} // namespace fun
