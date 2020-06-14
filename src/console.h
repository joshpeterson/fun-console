#pragma once

#include <string>

namespace easy
{

void console(const char* message);

class Console
{
public:
  std::string Format(const std::string& message);
  std::string AddNewLine(const std::string& message);
  std::string ReplaceEmoji(const std::string& message);
};

} // namespace easy
