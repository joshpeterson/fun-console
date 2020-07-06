#include "platform.h"

#if TARGET_POSIX

#include "platform-posix.h"

#include <cstdio>
#include <unistd.h>

namespace fun
{
static bool supportsControlCharacters = true;

PlatformPosix::PlatformPosix()
{
  supportsControlCharacters = isatty(STDOUT_FILENO) == 1;
}

bool PlatformPosix::SupportsControlCharacters() const
{
  return supportsControlCharacters;
}
} // namespace fun

#endif // TARGET_POSIX
