#pragma once

#include "platform.h"

#include <memory>
#include <string>

namespace fun
{

void console(const char* message);
void console(const std::string& message);

class Console
{
public:
  Console();
  explicit Console(const Platform* platform);
  std::string Format(const std::string& message);
  std::string AddNewLine(const std::string& message);

private:
  std::unique_ptr<const Platform> platform_;
};

} // namespace fun
