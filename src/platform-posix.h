#pragma once

#include "platform.h"

namespace fun
{
class PlatformPosix : public Platform
{
public:
  PlatformPosix();
  bool SupportsControlCharacters() const override;
};
} // namespace fun
