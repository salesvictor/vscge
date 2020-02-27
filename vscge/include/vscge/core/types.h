#ifndef VSCGE_INCLUDE_VSCGE_CORE_TYPES_H
#define VSCGE_INCLUDE_VSCGE_CORE_TYPES_H

#include <Windows.h>

namespace vs {
struct Point {
  short x;
  short y;
};

struct Size {
  short width;
  short height;

  short Area() const { return width * height; };
  operator COORD() const { return {width, height}; };
};

struct Rect {
  short x;
  short y;

  union {
    struct {
      short width;
      short height;
    };

    Size size;
  };

  short BufferSize() const { return width * height; };

  Point TopLeft() const { return {x, y}; };
  Point BottomRight() const { return {x + width, y + height}; };

  bool Contains(const Point &p) { return x <= p.x && p.x < x + width && y <= p.y && p.y < y + height; };

  operator SMALL_RECT() const { return {x, y, x + width - 1, y + height - 1}; };
};

struct Pixel {
  union {
    struct {
      short x;
      short y;
    };

    Point location;
  };

  CHAR_INFO info;

  Pixel(wchar_t ch, Point location) : location(location){
    info = {
      .Char = { .UnicodeChar = ch },
      .Attributes = 0x000F,
    };
  }

  wchar_t Char() const { return info.Char.UnicodeChar; };
  wchar_t& Char() { return info.Char.UnicodeChar; };
};
} // namespace vs

#endif // VSCGE_INCLUDE_VSCGE_CORE_TYPES_H