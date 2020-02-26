#include "vscge/application.h"

#include "vscge/utils/conversions.h"

#include <algorithm>
#include <vector>
#include <thread>

#include <Windows.h>

namespace vs {
Application::Application(const Size &screen_size, const Size &font_size)
    : screen_size_(screen_size),
      font_size_(font_size) {
  buffer_in_ = GetStdHandle(STD_INPUT_HANDLE);
  buffer_out_ = GetStdHandle(STD_OUTPUT_HANDLE);

  window_ = { 0, 0, 1, 1 };
  SetConsoleWindowInfo(buffer_out_, true, &(SMALL_RECT)window_);

  SetConsoleScreenBufferSize(buffer_out_, screen_size_);

  window_.size = Size(screen_size_);
  SetConsoleWindowInfo(buffer_out_, true, &(SMALL_RECT)window_);

  CONSOLE_FONT_INFOEX cfi = {
    .cbSize = sizeof(CONSOLE_FONT_INFOEX),
    .nFont = 0,
    .dwFontSize = font_size_,
    .FontFamily = FF_DONTCARE,
    .FontWeight = FW_NORMAL,
    .FaceName = L"Consolas",
  };
  SetCurrentConsoleFontEx(buffer_out_, false, &cfi);

  SetConsoleMode(buffer_in_, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
  SetConsoleActiveScreenBuffer(buffer_out_);

  screen_buffer_.reserve(screen_size_.Area());
  for (int i=0;i<screen_size_.Area();++i) {
    auto [x, y] = BufferIndexToPoint(window_, i);

    screen_buffer_.push_back(Pixel(L' ', {x, y}));
  }
}

void Application::Start() {
  OnStart();

  std::thread game_loop(&Application::MainLoop, this);
  game_loop.join();
}

void Application::MainLoop() {
  while (true) {
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(20ms);
    OnUpdate();

    std::vector<CHAR_INFO> write_buffer;
    for (const auto &pixel : screen_buffer_) {
      write_buffer.push_back(pixel.info);
    }
    WriteConsoleOutput(buffer_out_, write_buffer.data(), screen_size_, {0, 0},
                      &(SMALL_RECT)window_);
  }
}

void Application::SetPixel(const Pixel &pixel) {
  screen_buffer_[vs::PointToBufferIndex(window_, pixel.location)] = pixel;
}

void Application::DrawBuffer(const std::vector<Pixel> &buffer) {
  for (const auto &pixel : buffer) {
    SetPixel(pixel);
  }
}

void Application::DrawLine(const Point &p1, const Point &p2) {
  auto isLeft = [](const Point &a, const Point &b) {
    if (a.x == b.x) {
      return a.y < b.y;
    }

    return a.x < b.x;
  };

  auto [p_left, p_right] = std::minmax(p1, p2, isLeft);

  if (p_left.x == p_right.x) {
    // Treat vertical lines
    for (short y = p_left.y; y <= p_right.y; ++y) {
      SetPixel(Pixel(0x2588, {p_left.x, y}));
    }
  } else {
    short dx = p_right.x - p_left.x;
    short dy = p_right.y - p_left.y;

    for (short x = p_left.x; x <= p_right.x; ++x) {
      short y = (short)((float)dy/dx * (x - p_left.x) + p_left.y);
      SetPixel(Pixel(0x2588, {x, y}));
    }
  }
}

void Application::DrawRect(const Rect &rect) {
  short x0 = rect.x;
  short y0 = rect.y;
  short x1 = rect.x + rect.width - 1;
  short y1 = rect.y + rect.height - 1;

  DrawLine({x0, y0}, {x1, y0}); // Top
  DrawLine({x1, y0}, {x1, y1}); // Right
  DrawLine({x1, y1}, {x0, y1}); // Bottom
  DrawLine({x0, y1}, {x0, y0}); // Left
}
} // namespace vs