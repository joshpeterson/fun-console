#pragma once

#include "platform.h"

namespace easy
{
class PlatformWindows : public Platform
{
public:
  PlatformWindows();
  bool SupportsEmoji() const override;
};
} // namespace easy
