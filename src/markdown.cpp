#include "markdown.h"

namespace fun
{

static bool found(std::string::size_type location)
{
  return location != std::string::npos;
}

static std::string formatting_code(char marker)
{
  if (marker == '*')
    return "\033[1m";

  if (marker == '_')
    return "\033[3m";

  return std::string(1, marker);
}

std::string Markdown::Replace(const std::string& message)
{
  std::string result = message;
  for (size_t i = 0; i < result.length(); ++i)
  {
    auto marker_start = std::string::npos;
    auto marker_end = std::string::npos;
    char marker = 0;

    // Check for unescaped markers and spaces after markers
    if ((result[i] == '*' || result[i] == '_') &&
        (i == 0 || result[i - 1] != '\\') &&
        (i == result.length() || result[i + 1] != ' '))
    {
      marker_start = i;
      marker = result[i];

      // Check for two markers in a row and treat them like one
      bool double_marker = false;
      if (i + 1 < result.length() && result[i + 1] == marker)
      {
        double_marker = true;
      }

      int num_to_replace = double_marker ? 2 : 1;

      marker_end = result.find_first_of(marker, marker_start + num_to_replace);

      if (double_marker && !(marker_end + 1 < result.length() &&
                             result[marker_end + 1] == marker))
        marker_end = std::string::npos; // Second double marker not found

      if (found(marker_start) && found(marker_end))
      {
        // Replace the first markdown marker with the proper escape sequence.
        result.replace(marker_start, num_to_replace, formatting_code(marker));

        // Advance the previous markdown end marker the number of characters
        // we inserted to replace the first marker.
        marker_end += 3;
        if (double_marker)
          marker_end -= 1;

        // Now replace the second marker
        result.replace(marker_end, num_to_replace, "\033[0m");

        // Advance the index the total number of characters we have inserted.
        i += 6;
      }
    }
  }

  return result;
}

} // namespace fun
