#pragma once

#include "platform.h"

namespace easy
{
class PlatformFactory
{
public:
  static const Platform* Current();
};
} // namespace easy
