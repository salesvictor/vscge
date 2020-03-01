#include "vscge/core/renderer.h"

#include <algorithm>
#include <cassert>
#include <cwchar>
#include <vector>

#include "vscge/core/types.h"
#include "vscge/utils/conversions.h"

namespace vs::Renderer {
struct Internals {
  std::vector<Pixel> screen_buffer;
  Window window;

  SMALL_RECT window_wrapper;

  std::wstring font = L"Consolas";
  Size font_size;
};

Internals internals;

void Initialize(const HANDLE &handle, const Size &window_size,
                const Size &font_size) {
  internals.window = {handle, window_size};
  internals.font_size = font_size;
  internals.window_wrapper = SMALL_RECT(Rect(internals.window));

  // Font needs to be set before knowing largest possible size.
  CONSOLE_FONT_INFOEX cfi = {
      .cbSize = sizeof(CONSOLE_FONT_INFOEX),
      .nFont = 0,
      .dwFontSize = internals.font_size,
      .FontFamily = FF_DONTCARE,
      .FontWeight = FW_NORMAL,
  };
  wcsncpy_s(cfi.FaceName, internals.font.c_str(), 32);  // NOLINT: C API...
  SetCurrentConsoleFontEx(internals.window.handle, false, &cfi);

  COORD largest_size = GetLargestConsoleWindowSize(handle);
  if (window_size.width > largest_size.X ||
      window_size.height > largest_size.Y) {
    MessageBox(GetConsoleWindow(), TEXT("Window size is too big!"), nullptr,
               MB_OK);
    return;
  }

  SetConsoleScreenBufferSize(internals.window.handle, internals.window.size);
  SetConsoleWindowInfo(internals.window.handle, true,
                       &internals.window_wrapper);

  CONSOLE_CURSOR_INFO cci = {
      .dwSize = 1,
      .bVisible = false,
  };
  SetConsoleCursorInfo(internals.window.handle, &cci);
  SetConsoleActiveScreenBuffer(internals.window.handle);
  internals.screen_buffer.reserve(internals.window.size.Area());
  for (int i = 0; i < internals.window.size.Area(); ++i) {
    internals.screen_buffer.emplace_back(Pixel(
        BufferIndexToPoint(Rect(internals.window), i), {PixelBlock::kEmpty}));
  }
}

const std::vector<Pixel> &GetBuffer() { return internals.screen_buffer; }

const Pixel &GetPixelAt(Point location) {
  return internals
      .screen_buffer[PointToBufferIndex(Rect(internals.window), location)];
}

const Rect GetWindowRect() { return Rect(internals.window); }

void DrawPixel(const Pixel &pixel) {
  assert(Rect(internals.window).Contains(pixel.location));
  internals.screen_buffer[PointToBufferIndex(Rect(internals.window),
                                             pixel.location)] = pixel;
}

void ClearScreen() {
  for (auto &pixel : internals.screen_buffer) {
    pixel.Char() = PixelBlock::kEmpty;
    pixel.Color() = PixelColor();
  }
}

void DrawBuffer(const std::vector<Pixel> &buffer) {
  assert(buffer.size() <= internals.screen_buffer.size());
  for (const auto &pixel : buffer) DrawPixel(pixel);
}

void DrawLine(const Point &p1, const Point &p2, const PixelProps &props) {
  auto isLeft = [](const Point &a, const Point &b) {
    if (a.x == b.x) return a.y < b.y;

    return a.x < b.x;
  };

  auto [p_left, p_right] = std::minmax(p1, p2, isLeft);

  if (p_left.x == p_right.x) {
    // Treat vertical lines
    for (int y = p_left.y; y <= p_right.y; ++y) {
      DrawPixel(Pixel({p_left.x, y}, props));
    }
  } else {
    int dx = p_right.x - p_left.x;
    int dy = p_right.y - p_left.y;

    for (int x = p_left.x; x <= p_right.x; ++x) {
      int y = dy / dx * (x - p_left.x) + p_left.y;
      DrawPixel(Pixel({x, y}, props));
    }
  }
}

void DrawRect(const Rect &rect, const vs::PixelProps &props) {
  int x0 = rect.x;
  int y0 = rect.y;
  int x1 = rect.x + rect.width - 1;
  int y1 = rect.y + rect.height - 1;

  DrawLine({x0, y0}, {x1, y0}, props);  // Top
  DrawLine({x1, y0}, {x1, y1}, props);  // Right
  DrawLine({x1, y1}, {x0, y1}, props);  // Bottom
  DrawLine({x0, y1}, {x0, y0}, props);  // Left
}

void FillRect(const Rect &rect, const vs::PixelProps &props) {
  for (int y = rect.y; y < internals.window.size.height; ++y) {
    DrawLine({rect.x, y}, {rect.x + rect.width, y}, props);
  }
}

void Render() {
  std::vector<CHAR_INFO> write_buffer;
  for (const auto &pixel : internals.screen_buffer) {
    write_buffer.emplace_back(pixel.props);
  }
  WriteConsoleOutput(internals.window.handle, write_buffer.data(),
                     internals.window.size, {0, 0}, &internals.window_wrapper);
}
}  // namespace vs::Renderer