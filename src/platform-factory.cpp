#include "platform-factory.h"

#include "platform-posix.h"
#include "platform-windows.h"

namespace fun
{
const Platform* PlatformFactory::Current()
{
#if TARGET_WINDOWS
  return new PlatformWindows();
#elif TARGET_POSIX
  return new PlatformPosix();
#else
  return new Platform();
#endif
}
} // namespace fun
