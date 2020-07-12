#include "markdown.h"

namespace fun
{

static bool found(std::string::size_type location)
{
  return location != std::string::npos;
}

static std::string formattingCode(char marker)
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
    auto markerStart = std::string::npos;
    auto markerEnd = std::string::npos;
    char marker = 0;

    // Check for unescaped markers and spaces after markers
    if ((result[i] == '*' || result[i] == '_') &&
        (i == 0 || result[i - 1] != '\\') &&
        (i == result.length() || result[i + 1] != ' '))
    {
      markerStart = i;
      marker = result[i];

      // Check for two markers in a row and treat them like one
      bool doubleMarker = false;
      if (i + 1 < result.length() && result[i + 1] == marker)
      {
        doubleMarker = true;
      }

      int numToReplace = doubleMarker ? 2 : 1;

      markerEnd = result.find_first_of(marker, markerStart + numToReplace);

      if (doubleMarker &&
          !(markerEnd + 1 < result.length() && result[markerEnd + 1] == marker))
        markerEnd = std::string::npos; // Second double marker not found

      if (found(markerStart) && found(markerEnd))
      {
        // Replace the first markdown marker with the proper escape sequence.
        result.replace(markerStart, numToReplace, formattingCode(marker));

        // Advance the previous markdown end marker the number of characters
        // we inserted to replace the first marker.
        markerEnd += 3;
        if (doubleMarker)
          markerEnd -= 1;

        // Now replace the second marker
        result.replace(markerEnd, numToReplace, "\033[0m");

        // Advance the index the total number of characters we have inserted.
        i += 6;
      }
    }
  }

  return result;
}

} // namespace fun
