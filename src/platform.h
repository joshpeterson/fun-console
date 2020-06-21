#pragma once

#if defined(_WIN32) || defined(WIN32)
#define TARGET_WINDOWS 1
#endif

namespace fun
{

class Platform
{
public:
  // These are required because of the virtual method
  Platform() = default;
  Platform(const Platform&) = delete;
  Platform& operator=(const Platform&) = delete;
  Platform(Platform&&) = delete;
  Platform& operator=(Platform&&) = delete;
  virtual ~Platform() = default;

  virtual bool SupportsEmoji() const;
};

} // namespace fun
