#ifndef VSCGE_INCLUDE_VSCGE_CONSTS_H
#define VSCGE_INCLUDE_VSCGE_CONSTS_H

namespace vs {
enum PixelBlock : wchar_t {
  kUpperHalf = 0x2580,    // ▀
  kLowerHalf = 0x2584,    // ▄
  kFull = 0x2588,         // █
  kLightShade = 0x2591,   //   ░
  kMediumShade = 0x2592,  //     ▒
  kDarkShade = 0x2593,    // ▓
};

namespace PixelColor {
namespace {
enum FG : WORD {
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
}  // namespace

enum BG : WORD {
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
}  // namespace PixelColor
}  // namespace vs
#endif  // VSCGE_INCLUDE_VSCGE_CONSTS_H