#include "platform.h"

#if TARGET_WINDOWS

#include "platform-windows.h"

#include <Windows.h>

#include <cstdio>

namespace fun
{

static bool supportsEmoji = false;
static bool supportsControlCharacters = false;

static bool HasEnvironmentVariable(const char* variable)
{
  if (GetEnvironmentVariable(variable, NULL, 0) == 0 &&
      GetLastError() == ERROR_ENVVAR_NOT_FOUND)
    return false;
  return true;
}

static bool IsWindowsTerminal()
{
  return HasEnvironmentVariable("WT_PROFILE_ID") ||
         HasEnvironmentVariable("WT_SESSION");
}

static bool IsConEmu() { return HasEnvironmentVariable("ConEmuBuild"); }

PlatformWindows::PlatformWindows()
{
  const int utf8CodePage = 65001;
  BOOL succeeded = SetConsoleOutputCP(utf8CodePage);
  if (!succeeded)
    supportsEmoji = false;

  if (IsWindowsTerminal() || IsConEmu())
  {
    supportsEmoji = true;
    supportsControlCharacters = true;
  }

  HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
  if (outputHandle == INVALID_HANDLE_VALUE)
  {
    supportsEmoji = false;
    supportsControlCharacters = false;
    return;
  }

  DWORD dwMode = 0;
  if (!GetConsoleMode(outputHandle, &dwMode))
  {
    supportsEmoji = false;
    supportsControlCharacters = false;
    return;
  }

  dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
  if (!SetConsoleMode(outputHandle, dwMode))
  {
    supportsControlCharacters = false;
    return;
  }
}

bool PlatformWindows::SupportsEmoji() const { return supportsEmoji; }

bool PlatformWindows::SupportsControlCharacters() const
{
  return supportsControlCharacters;
}

} // namespace fun

#endif // TARGET_WINDOWS
