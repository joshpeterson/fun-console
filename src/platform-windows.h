#pragma once

#include "platform.h"

namespace fun
{
class PlatformWindows : public Platform
{
public:
  PlatformWindows();
  bool SupportsEmoji() const override;
  bool SupportsControlCharacters() const override;
};
} // namespace fun
