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

static bool try_get_formatting_code(const std::string& color,
                                    std::string& formatting_code)
{
  auto possibleColor = colors.find(color);
  if (!found(possibleColor))
    return false;

  formatting_code = possibleColor->second;
  return true;
}

static std::string::size_type try_find_end_of_color(std::string const& result,
                                                    size_t i,
                                                    const std::string& color)
{
  std::string end_of_color_marker = "[/";
  end_of_color_marker += color;
  end_of_color_marker += "]";
  auto end_of_color = result.find(end_of_color_marker, i);
  return end_of_color;
}

std::string Colors::Replace(std::string const& message)
{
  std::string result = message;
  auto marker_start = std::string::npos;
  auto marker_end = std::string::npos;
  std::string color;

  for (size_t i = 0; i < result.length(); ++i)
  {
    if (result[i] == '[')
    {
      marker_start = i;
    }
    else if (found(marker_start))
    {
      if (result[i] == ']')
        marker_end = i;
      else
        color += result[i];
    }

    if (found(marker_start) && found(marker_end))
    {
      std::string formatting_code;
      if (try_get_formatting_code(color, formatting_code))
      {
        auto end_of_color = try_find_end_of_color(result, i, color);
        if (found(end_of_color))
        {
          result.replace(marker_start, marker_end - marker_start + 1,
                         formatting_code);
          end_of_color += formatting_code.length() - color.length() - 2;
          result.replace(end_of_color, color.length() + 3, "\033[0m");
          i = end_of_color + 3;
          marker_start = std::string::npos;
          marker_end = std::string::npos;
          color = "";
        }
      }
    }
  }
  return result;
}
} // namespace fun
