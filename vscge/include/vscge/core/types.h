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

  inline int Area() const { return width * height; };
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

  inline int BufferSize() const { return width * height; };

  inline Point TopLeft() const { return {x, y}; };
  inline Point BottomRight() const { return {x + width, y + height}; };

  inline bool Contains(const Point& p) const {
    return x <= p.x && p.x < x + width && y <= p.y && p.y < y + height;
  };

  inline operator SMALL_RECT() const {
    return {(SHORT)x, (SHORT)y, (SHORT)(x + width - 1),
            (SHORT)(y + height - 1)};
  };
};

struct PixelColor {
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

  PixelColor() : color((int)BG::kBlack | (int)FG::kWhite){};
  PixelColor(BG back) : color((int)back | (int)FG::kWhite){};
  PixelColor(FG fore) : color((int)BG::kBlack | (int)fore){};
  PixelColor(BG back, FG fore) : color((int)back | (int)fore){};

  operator WORD() const { return (WORD)color; };
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
        .Attributes = PixelColor{},
    };
  }
  Pixel(wchar_t ch, PixelColor color, Point location) : location(location) {
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

struct Window {
  HANDLE handle;
  Size size;

  operator Rect() const { return {0, 0, size.width, size.height}; }
};
}  // namespace vs

#endif  // VSCGE_INCLUDE_VSCGE_CORE_TYPES_H