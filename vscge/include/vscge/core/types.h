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

#include <Windows.h>

#include "vscge/core/core.h"

namespace vs {
struct VS_API Point {
  int x;
  int y;

  Point() = default;
  constexpr Point(const int &x, const int &y) : x(x), y(y) {}
  constexpr Point(const COORD &coord) : x(coord.X), y(coord.Y) {}

  Point &operator+=(const Point &other) {
    x += other.x;
    y += other.y;

    return *this;
  };
  friend Point operator+(Point lhs, const Point &rhs) {
    lhs += rhs;
    return lhs;
  };

  Point &operator-=(const Point &other) {
    x -= other.x;
    y -= other.y;

    return *this;
  };
  friend Point operator-(Point lhs, const Point &rhs) {
    lhs -= rhs;
    return lhs;
  };
};

struct VS_API Size {
  int width;
  int height;

  constexpr int Area() const { return width * height; };
  constexpr operator COORD() const { return {(SHORT)width, (SHORT)height}; };
};

template <class Elem>
class VS_API Matrix {
 public:
  Matrix() = default;
  Matrix(int rows, int cols) : size_({rows, cols}), data_(size_.Area()) {}
  Matrix(int rows, int cols, const Elem &default_elem) : Matrix(rows, cols) {
    for (auto &elem : data_) {
      elem = default_elem;
    }
  }
  Matrix(Size size) : Matrix(size.width, size.height) {}
  Matrix(Size size, const Elem &default_elem)
      : Matrix(size.width, size.height, default_elem) {}

  Elem &operator()(int row, int col) {
    return const_cast<Elem &>(std::as_const(*this)(row, col));
  }
  const Elem &operator()(int row, int col) const {
    return data_[row * size_.width + col];
  }

  Elem &operator()(Point location) { return (*this)(location.y, location.x); }
  const Elem &operator()(Point location) const {
    return (*this)(location.x, location.y);
  }

  const std::vector<Elem> &Buffer() const { return data_; }

 private:
  Size size_;
  std::vector<Elem> data_;
};

struct VS_API Rect {
  int x;
  int y;

  union {
    struct {
      int width;
      int height;
    };

    Size size;
  };

  constexpr int BufferSize() const { return width * height; };

  constexpr Point TopLeft() const { return {x, y}; };
  constexpr Point BottomRight() const { return {x + width, y + height}; };

  constexpr bool Contains(const Point &p) const {
    return x <= p.x && p.x < x + width && y <= p.y && p.y < y + height;
  };

  // TODO(Victor): Move to a platform layer.
  constexpr operator SMALL_RECT() const {
    return {(SHORT)x, (SHORT)y, (SHORT)(x + width - 1),
            (SHORT)(y + height - 1)};
  };
};

// TODO(Victor): Move to a platform layer.
enum PixelBlock {
  kEmpty = ' ',
  kUpperHalf = 223,    // ▀
  kLowerHalf = 220,    // ▄
  kFull = 219,         // █
  kLightShade = 176,   // ░
  kMediumShade = 177,  // ▒
  kDarkShade = 178,    // ▓
  kBlackSquare = 254,  // ■
};

// TODO(Victor): Move to a platform layer.
struct VS_API PixelColor {
  enum class FG {
    kBlack = 0X0000,
    kDarkBlue = 0X0001,
    kDarkGreen = 0X0002,
    kDarkCyan = 0X0003,
    kDarkRed = 0X0004,
    kDarkMagenta = 0X0005,
    kDarkYellow = 0X0006,
    kGrey = 0X0007,
    kDarkGrey = 0X0008,
    kBlue = 0X0009,
    kGreen = 0X000A,
    kCyan = 0X000B,
    kRed = 0X000C,
    kMagenta = 0X000D,
    kYellow = 0X000E,
    kWhite = 0x000F,
  };

  enum class BG {
    kBlack = 0X0000,
    kDarkBlue = 0x0010,
    kDarkGreen = 0x0020,
    kDarkCyan = 0x0030,
    kDarkRed = 0x0040,
    kDarkMagenta = 0x0050,
    kDarkYellow = 0x0060,
    kGrey = 0X0070,
    kDarkGrey = 0x0080,
    kBlue = 0X0090,
    kGreen = 0X00A0,
    kCyan = 0X00B0,
    kRed = 0X00C0,
    kMagenta = 0x00D0,
    kYellow = 0X00E0,
    kWhite = 0X00F0,
  };

  int color;

  constexpr PixelColor() : color((int)BG::kBlack | (int)FG::kWhite) {}
  constexpr PixelColor(const BG &back) : color((int)back | (int)FG::kWhite) {}
  constexpr PixelColor(const FG &fore) : color((int)BG::kBlack | (int)fore) {}
  constexpr PixelColor(const BG &back, const FG &fore)
      : color((int)back | (int)fore) {}

  // TODO(Victor): Move to a platform layer.
  constexpr operator WORD() const { return (WORD)color; };
};

// TODO(Victor): Pixels certainly have colors, but they will also have different
// properties depending on what we are trying to do with it. For example, `char`
// is valid only on a Console application, and PixelBlock will not make sense
// anywhere else too...
struct VS_API PixelProps {
  PixelColor color;
  union {
    PixelBlock block;
    char ch;
  };

  constexpr PixelProps() : block(PixelBlock::kEmpty), color() {}
  constexpr explicit PixelProps(const PixelBlock &block)
      : block(block), color(PixelColor::BG::kWhite) {}
  constexpr explicit PixelProps(const char &ch) : ch(ch), color() {}
  constexpr explicit PixelProps(const PixelColor &color)
      : block(PixelBlock::kEmpty) {}
  constexpr PixelProps(const PixelColor &color, const PixelBlock &block)
      : color(color), block(block) {}
  constexpr PixelProps(const PixelColor &color, const char &ch)
      : color(color), ch(ch) {}

  // TODO(Victor): Move to a platform layer.
  constexpr operator CHAR_INFO() const {
    return {.Char = {.AsciiChar = ch}, .Attributes = color};
  }
};

struct VS_API Pixel {
  union {
    struct {
      int x;
      int y;
    };

    Point location;
  };

  PixelProps props;

  Pixel() = default;

  constexpr Pixel(const Point &location, const PixelProps &props)
      : location(location), props(props) {}

  PixelBlock &Char() { return props.block; }
  constexpr const PixelBlock &Char() const { return props.block; }

  PixelColor &Color() { return props.color; };
  constexpr const PixelColor &Color() const { return props.color; }
};

struct VS_API Window {
  // TODO(Victor): Move to a platform layer.
  HANDLE handle;
  Size size;

  constexpr operator Rect() const { return {0, 0, size.width, size.height}; }
};
}  // namespace vs

#endif  // VSCGE_INCLUDE_VSCGE_CORE_TYPES_H_
