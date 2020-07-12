#include "colors.h"

#include <unordered_map>

namespace fun
{

static bool found(std::string::size_type location)
{
  return location != std::string::npos;
}

static std::unordered_map<std::string, std::string> colors = {
    {"black", "\033[30m"},        {"red", "\033[31m"},
    {"green", "\033[32m"},        {"yellow", "\033[33m"},
    {"blue", "\033[34m"},         {"magenta", "\033[35m"},
    {"cyan", "\033[36m"},         {"white", "\033[37m"},
    {"bright black", "\033[90m"}, {"bright red", "\033[91m"},
    {"bright green", "\033[92m"}, {"bright yellow", "\033[93m"},
    {"bright blue", "\033[94m"},  {"bright magenta", "\033[95m"},
    {"bright cyan", "\033[96m"},  {"bright white", "\033[97m"},
};

static bool found(std::unordered_map<std::string, std::string>::iterator color)
{
  return color != colors.end();
}

static bool tryGetFormattingCode(const std::string& color,
                                 std::string& formattingCode)
{
  auto possibleColor = colors.find(color);
  if (!found(possibleColor))
    return false;

  formattingCode = possibleColor->second;
  return true;
}

static std::string::size_type
tryFindEndOfColor(std::string const& result, size_t i, const std::string& color)
{
  std::string endOfColorMarker = "[/";
  endOfColorMarker += color;
  endOfColorMarker += "]";
  auto endOfColor = result.find(endOfColorMarker, i);
  return endOfColor;
}

std::string Colors::Replace(std::string const& message)
{
  std::string result = message;
  auto markerStart = std::string::npos;
  auto markerEnd = std::string::npos;
  std::string color;

  for (size_t i = 0; i < result.length(); ++i)
  {
    if (result[i] == '[')
    {
      markerStart = i;
    }
    else if (found(markerStart))
    {
      if (result[i] == ']')
        markerEnd = i;
      else
        color += result[i];
    }

    if (found(markerStart) && found(markerEnd))
    {
      std::string formattingCode;
      if (tryGetFormattingCode(color, formattingCode))
      {
        auto endOfColor = tryFindEndOfColor(result, i, color);
        if (found(endOfColor))
        {
          result.replace(markerStart, markerEnd - markerStart + 1,
                         formattingCode);
          endOfColor += formattingCode.length() - color.length() - 2;
          result.replace(endOfColor, color.length() + 3, "\033[0m");
          i = endOfColor + 3;
          markerStart = std::string::npos;
          markerEnd = std::string::npos;
          color = "";
        }
      }
    }
  }
  return result;
}
} // namespace fun
