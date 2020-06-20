#include "platform.h"

#if TARGET_WINDOWS

#include "platform-windows.h"

#include <Windows.h>

#include <cstdio>

namespace easy
{

static bool supportsEmoji = false;

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
    supportsEmoji = true;
}

bool PlatformWindows::SupportsEmoji() const { return supportsEmoji; }

} // namespace easy

#endif // TARGET_WINDOWS
