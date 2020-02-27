#ifndef VSCGE_INCLUDE_VSCGE_CORE_TYPES_H
#define VSCGE_INCLUDE_VSCGE_CORE_TYPES_H

#include <Windows.h>

#include "vscge/core/consts.h"


namespace vs {
struct Point {
  int x;
  int y;
};

struct Size {
  int width;
  int height;

  int Area() const { return width * height; };
  operator COORD() const { return {(SHORT)width, (SHORT)height}; };
};

struct Rect {
  int x;
  int y;

  union {
    struct {
      int width;
      int height;
    };

    Size size;
  };

  int BufferSize() const { return width * height; };

  Point TopLeft() const { return {x, y}; };
  Point BottomRight() const { return {x + width, y + height}; };

  bool Contains(const Point& p) {
    return x <= p.x && p.x < x + width && y <= p.y && p.y < y + height;
  };

  operator SMALL_RECT() const {
    return {(SHORT)x, (SHORT)y, (SHORT)(x + width - 1),
            (SHORT)(y + height - 1)};
  };
};

struct Pixel {
  union {
    struct {
      int x;
      int y;
    };

    Point location;
  };

  CHAR_INFO info;

  Pixel(wchar_t ch, Point location) : location(location) {
    info = {
        .Char = {.UnicodeChar = ch},
        .Attributes = PixelColor::FG::kWhite,
    };
  }
  Pixel(wchar_t ch, PixelColor::FG color, Point location) : location(location) {
    info = {
        .Char = {.UnicodeChar = ch},
        .Attributes = color,
    };
  }

  wchar_t& Char() { return info.Char.UnicodeChar; };
  const wchar_t& Char() const { return info.Char.UnicodeChar; };

  WORD& Color() { return info.Attributes; };
  const WORD& Color() const { return info.Attributes; };
};
}  // namespace vs

#endif  // VSCGE_INCLUDE_VSCGE_CORE_TYPES_H