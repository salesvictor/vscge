// Copyright 2020 Victor Sales
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "vscge/core/types.h"

namespace vs {
struct VS_API VertexColor {
  enum class FG {
    kBlack       = 0X0000,
    kDarkBlue    = 0X0001,
    kDarkGreen   = 0X0002,
    kDarkCyan    = 0X0003,
    kDarkRed     = 0X0004,
    kDarkMagenta = 0X0005,
    kDarkYellow  = 0X0006,
    kGrey        = 0X0007,
    kDarkGrey    = 0X0008,
    kBlue        = 0X0009,
    kGreen       = 0X000A,
    kCyan        = 0X000B,
    kRed         = 0X000C,
    kMagenta     = 0X000D,
    kYellow      = 0X000E,
    kWhite       = 0x000F,
  };

  enum class BG {
    kBlack       = 0X0000,
    kDarkBlue    = 0x0010,
    kDarkGreen   = 0x0020,
    kDarkCyan    = 0x0030,
    kDarkRed     = 0x0040,
    kDarkMagenta = 0x0050,
    kDarkYellow  = 0x0060,
    kGrey        = 0X0070,
    kDarkGrey    = 0x0080,
    kBlue        = 0X0090,
    kGreen       = 0X00A0,
    kCyan        = 0X00B0,
    kRed         = 0X00C0,
    kMagenta     = 0x00D0,
    kYellow      = 0X00E0,
    kWhite       = 0X00F0,
  };

  int color;

  constexpr VertexColor() : color((int)BG::kBlack | (int)FG::kWhite) {}
  constexpr VertexColor(const BG& back) : color((int)back | (int)FG::kWhite) {}
  constexpr VertexColor(const FG& fore) : color((int)BG::kBlack | (int)fore) {}
  constexpr VertexColor(const BG& back, const FG& fore)
      : color((int)back | (int)fore) {}

  // TODO(Victor): Move to a platform layer.
  constexpr operator WORD() const { return (WORD)color; };
};


VertexProps:
  union {
    VertexBlock block;
    char ch;
  };

  constexpr VertexProps() : block(VertexBlock::kEmpty), color() {}
  constexpr explicit VertexProps(const VertexBlock& block)
      : block(block), color(VertexColor::BG::kWhite) {}
  constexpr explicit VertexProps(const char& ch) : ch(ch), color() {}
  constexpr explicit VertexProps(const VertexColor& color)
      : block(VertexBlock::kEmpty) {}
  constexpr VertexProps(const VertexColor& color, const VertexBlock& block)
      : color(color), block(block) {}
  constexpr VertexProps(const VertexColor& color, const char& ch)
      : color(color), ch(ch) {}

  constexpr operator CHAR_INFO() const {
    return {.Char = {.AsciiChar = ch}, .Attributes = color};
  }

enum VertexBlock {
  kEmpty       = ' ',
  kUpperHalf   = 223,  // ▀
  kLowerHalf   = 220,  // ▄
  kFull        = 219,  // █
  kLightShade  = 176,  // ░
  kMediumShade = 177,  // ▒
  kDarkShade   = 178,  // ▓
  kBlackSquare = 254,  // ■
};

  Vertex:
  VertexBlock& Char() { return props.block; }
  constexpr const VertexBlock& Char() const { return props.block; }

  VertexColor& Color() { return props.color; };
  constexpr const VertexColor& Color() const { return props.color; }
}  // namespace vs