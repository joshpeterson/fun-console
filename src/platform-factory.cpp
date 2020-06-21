#include "platform-factory.h"

#include "platform-windows.h"

namespace fun
{
const Platform* PlatformFactory::Current()
{
#if TARGET_WINDOWS
  return new PlatformWindows();
#else
  return new Platform();
#endif
}
} // namespace fun