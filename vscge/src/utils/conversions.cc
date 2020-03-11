// Copyright 2020 Victor Sales
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "vscge/utils/conversions.h"

#include <cassert>
#include <stdexcept>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "vscge/core/types.h"
#include "vscge/debug/debug.h"
#include "vscge/instrumentation/profiler.h"

namespace vs {
Point BufferIndexToPoint(const Rect &region, int i) {
  VS_ASSERT(i < region.width * region.height);  // NOLINT
  int x = region.x + (i % region.width);        // NOLINT
  int y = region.y + (i / region.width);        // NOLINT

  return {x, y};
}

int PointToBufferIndex(const Rect &region, const Point &point) {
  VS_ASSERT(region.Contains(point));
  return (point.y - region.y) * region.width + (point.x - region.x);  // NOLINT
}

std::vector<Pixel> StringToPixelBuffer(
    std::string_view string_buffer, const Rect &region,
    std::unordered_map<char, PixelProps> char_map) {
  VS_ASSERT(string_buffer.size() == region.BufferSize());

  std::vector<Pixel> buffer;
  buffer.reserve(string_buffer.size());

  for (size_t i = 0; i < string_buffer.size(); ++i) {
    Point location = BufferIndexToPoint(region, i);
    buffer.emplace_back(Pixel(location, char_map[string_buffer[i]]));
  }

  return buffer;
}
}  // namespace vs
