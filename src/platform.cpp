#include "platform.h"

namespace fun
{

bool Platform::SupportsEmoji() const { return true; }
bool Platform::SupportsControlCharacters() const { return true; }

} // namespace fun
