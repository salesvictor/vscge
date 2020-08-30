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

#ifndef VSCGE_INCLUDE_VSCGE_CORE_TYPES_H_
#define VSCGE_INCLUDE_VSCGE_CORE_TYPES_H_

#include "vscge/api.h"

namespace vs {
struct VS_API Point {
  int x;
  int y;

  Point& operator+=(const Point& other) {
    x += other.x;
    y += other.y;

    return *this;
  }
  Point& operator-=(const Point& other) {
    x -= other.x;
    y -= other.y;

    return *this;
  }
};

inline Point operator+(Point left, const Point& right) {
  left += right;
  return left;
}
inline Point operator-(Point left, const Point& right) {
  left -= right;
  return left;
}

struct VS_API Size {
  int width;
  int height;

  [[nodiscard]] constexpr int Area() const { return width * height; };
  [[nodiscard]] constexpr float AspectRatio() const { return static_cast<float>(width) / static_cast<float>(height); }
};

struct VS_API Rect {
  int x;
  int y;

  int width;
  int height;

  [[nodiscard]] constexpr Size Size() const { return {width, height}; }
  [[nodiscard]] constexpr int BufferSize() const { return width * height; }

  [[nodiscard]] Point TopLeft() const { return {x, y}; }
  [[nodiscard]] Point BottomRight() const { return {x + width, y + height}; }

  [[nodiscard]] bool Contains(const Point& p) const {
    return x <= p.x && p.x < x + width && y <= p.y && p.y < y + height;
  }
};
}  // namespace vs

#endif  // VSCGE_INCLUDE_VSCGE_CORE_TYPES_H_
