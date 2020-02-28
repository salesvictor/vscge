#include "vscge/utils/conversions.h"

#include <cassert>
#include <stdexcept>
#include <string_view>
#include <vector>

#include "vscge/core/types.h"

namespace vs {
Point BufferIndexToPoint(const Rect &region, int i) {
  int x = region.x + (i % region.width);
  int y = region.y + (i / region.width);

  return {x, y};
}

int PointToBufferIndex(const Rect &region, const Point &point) {
  return (point.y - region.y) * region.width + (point.x - region.x);
}

std::vector<Pixel> StringToPixelBuffer(std::wstring_view string_buffer,
                                       const Rect &region) {
  assert(string_buffer.size() == region.BufferSize());

  std::vector<Pixel> buffer;
  buffer.reserve(string_buffer.size());

  for (size_t i = 0; i < string_buffer.size(); ++i) {
    Point location = BufferIndexToPoint(region, i);
    buffer.emplace_back(Pixel(string_buffer[i], location));
  }

  return buffer;
}
}  // namespace vs
