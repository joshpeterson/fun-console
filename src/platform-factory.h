#pragma once

#include "platform.h"

namespace fun
{
class PlatformFactory
{
public:
  static const Platform* Current();
};
} // namespace fun
