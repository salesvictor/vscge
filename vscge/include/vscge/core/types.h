// Copyright 2020 Victor Sales

#ifndef VSCGE_INCLUDE_VSCGE_CORE_TYPES_H_
#define VSCGE_INCLUDE_VSCGE_CORE_TYPES_H_

#include <Windows.h>

#include "vscge/core/core.h"

namespace vs {
struct VS_API Point {
  int x;
  int y;
};

struct VS_API Size {
  int width;
  int height;

  inline int Area() const { return width * height; };
  operator COORD() const { return {(SHORT)width, (SHORT)height}; };
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

  inline int BufferSize() const { return width * height; };

  inline Point TopLeft() const { return {x, y}; };
  inline Point BottomRight() const { return {x + width, y + height}; };

  inline bool Contains(const Point &p) const {
    return x <= p.x && p.x < x + width && y <= p.y && p.y < y + height;
  };

  inline operator SMALL_RECT() const {
    return {(SHORT)x, (SHORT)y, (SHORT)(x + width - 1),
            (SHORT)(y + height - 1)};
  };
};

enum PixelBlock : wchar_t {
  kEmpty = L' ',
  kUpperHalf = 0x2580,           // ▀
  kLowerHalf = 0x2584,           // ▄
  kFull = 0x2588,                // █
  kLightShade = 0x2591,          // ░
  kMediumShade = 0x2592,         // ▒
  kDarkShade = 0x2593,           // ▓
  kFisheye = 0x25C9,             // ◉
  kCircleVerticalFill = 0x25CD,  // ◍
  kBlackCircle = 0x25CF,         // ●
  kLargeCircle = 0x25EF,         // ◯
  kLargeBlackCircle = 0x2B24,    // ⬤
};

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

  operator WORD() const { return (WORD)color; };
};

struct VS_API PixelProps {
  PixelColor color;
  union {
    PixelBlock block;
    wchar_t ch;
  };

  constexpr PixelProps() : ch(PixelBlock::kFull), color() {}
  constexpr PixelProps(const PixelBlock &block)
      : block(block), color(PixelColor::BG::kWhite) {}
  constexpr PixelProps(const wchar_t &ch) : ch(ch), color() {}
  constexpr PixelProps(const PixelColor &color, const PixelBlock &block)
      : color(color), block(block) {}
  constexpr PixelProps(const PixelColor &color, const wchar_t &ch)
      : color(color), ch(ch) {}

  operator CHAR_INFO() const {
    return {.Char = {.UnicodeChar = ch}, .Attributes = color};
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

  constexpr Pixel(const Point &location, const PixelProps &props)
      : location(location), props(props) {}

  PixelBlock &Char() { return props.block; }
  const PixelBlock &Char() const { return props.block; }

  PixelColor &Color() { return props.color; };
  const PixelColor &Color() const { return props.color; };
};

struct VS_API Window {
  HANDLE handle;
  Size size;

  operator Rect() const { return {0, 0, size.width, size.height}; }
};
}  // namespace vs

#endif  // VSCGE_INCLUDE_VSCGE_CORE_TYPES_H_
