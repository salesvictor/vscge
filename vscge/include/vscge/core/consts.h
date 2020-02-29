#ifndef VSCGE_INCLUDE_VSCGE_CONSTS_H
#define VSCGE_INCLUDE_VSCGE_CONSTS_H

namespace vs {
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
}  // namespace vs
#endif  // VSCGE_INCLUDE_VSCGE_CONSTS_H