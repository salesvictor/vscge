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

#include "vscge/core/core.h"
#include "vscge/math/vector.h"

namespace vs {
using Point = Vec2i;

struct VS_API Size {
  int width;
  int height;

  constexpr int Area() const { return width * height; };
};

struct VS_API Rect {
  int x;
  int y;

  int width;
  int height;

  constexpr Size Size() const { return {width, height}; }
  constexpr int BufferSize() const { return width * height; }

  Point TopLeft() const { return Point(x, y); }
  Point BottomRight() const { return Point(x + width, y + height); }

  bool Contains(const Point& p) const {
    return x <= p.x && p.x < x + width && y <= p.y && p.y < y + height;
  }
};

struct VS_API Vertex {
  float x;
  float y;
  float z;
};

struct VS_API Window {
  // TODO(Victor): Move to a platform layer.
  // HANDLE handle;
  Size size;

  constexpr operator Rect() const { return {0, 0, size.width, size.height}; }
};
}  // namespace vs

#endif  // VSCGE_INCLUDE_VSCGE_CORE_TYPES_H_
