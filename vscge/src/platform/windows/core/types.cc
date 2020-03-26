#include "vscge/core/types.h"

#include <Windows.h>

namespace vs {
  Size:
constexpr operator COORD() {
  return {(SHORT)width, (SHORT)height};

};
Rect:
  constexpr operator SMALL_RECT() const {
    return {(SHORT)x, (SHORT)y, (SHORT)(x + width - 1),
            (SHORT)(y + height - 1)};
  };
}  // namespace vs