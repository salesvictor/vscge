#include "vscge/utils/conversions.h"

#include "vscge/core/types.h"

#include <stdexcept>
#include <string>
#include <vector>

namespace vs {
Point BufferIndexToPoint(const Rect &rect, int i) {
  short x = rect.x + (i % rect.width);
  short y = rect.y + ((short)i / rect.width);

  return {x, y};
}

int PointToBufferIndex(const Rect &region, const Point &point) {
  return (point.y - region.y) * region.width + (point.x - region.x);
}

std::vector<Pixel> StringToPixelBuffer(std::wstring_view string_buffer, const Rect &region) {
  if (string_buffer.size() != region.BufferSize()) {
    throw std::invalid_argument("string_buffer size must match region area.");
  }
  
  std::vector<Pixel> buffer;
  buffer.reserve(string_buffer.size());

  for (size_t i = 0; i < string_buffer.size(); ++i) {
    Point location = BufferIndexToPoint(region, i);
    buffer.push_back(Pixel(string_buffer[i], location));
  }

  return buffer;
}
} // namespace vs