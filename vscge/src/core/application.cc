#include "vscge/core/application.h"

#include <Windows.h>

#include <algorithm>
#include <string>
#include <thread>
#include <vector>

#include "vscge/core/consts.h"
#include "vscge/core/timer.h"
#include "vscge/utils/conversions.h"


namespace vs {
Application::Application(const Size &screen_size, const Size &font_size)
    : screen_size_(screen_size),
      font_size_(font_size),
      window_({0, 0, screen_size.width, screen_size.height}) {
  buffer_in_ = GetStdHandle(STD_INPUT_HANDLE);
  buffer_out_ = GetStdHandle(STD_OUTPUT_HANDLE);
  window_wrapper_ = SMALL_RECT(window_);

  SetConsoleScreenBufferSize(buffer_out_, screen_size_);

  SetConsoleWindowInfo(buffer_out_, true, &window_wrapper_);

  CONSOLE_FONT_INFOEX cfi = {
      .cbSize = sizeof(CONSOLE_FONT_INFOEX),
      .nFont = 0,
      .dwFontSize = font_size_,
      .FontFamily = FF_DONTCARE,
      .FontWeight = FW_NORMAL,
      .FaceName = L"Consolas",
  };
  SetCurrentConsoleFontEx(buffer_out_, false, &cfi);

  SetConsoleMode(buffer_in_, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT |
                                 ENABLE_MOUSE_INPUT);
  SetConsoleActiveScreenBuffer(buffer_out_);

  screen_buffer_.reserve(screen_size_.Area());
  for (int i = 0; i < screen_size_.Area(); ++i) {
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
  Timer timer;
  timer.Start();
  while (true) {
    Timestep timestep = timer.Stop();
    std::wstring title =
        std::wstring(L"VS CGS - FPS: ") + std::to_wstring(1 / timestep);
    SetConsoleTitleW(title.c_str());

    timer.Start();

    OnUpdate(timestep);

    std::vector<CHAR_INFO> write_buffer;
    for (const auto &pixel : screen_buffer_) {
      write_buffer.push_back(pixel.info);
    }
    WriteConsoleOutput(buffer_out_, write_buffer.data(), screen_size_, {0, 0},
                       &window_wrapper_);
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
    for (int y = p_left.y; y <= p_right.y; ++y) {
      SetPixel(Pixel(PixelBlock::kSolid, {p_left.x, y}));
    }
  } else {
    int dx = p_right.x - p_left.x;
    int dy = p_right.y - p_left.y;

    for (int x = p_left.x; x <= p_right.x; ++x) {
      int y = dy / dx * (x - p_left.x) + p_left.y;
      SetPixel(Pixel(PixelBlock::kSolid, {x, y}));
    }
  }
}

void Application::DrawRect(const Rect &rect) {
  int x0 = rect.x;
  int y0 = rect.y;
  int x1 = rect.x + rect.width - 1;
  int y1 = rect.y + rect.height - 1;

  DrawLine({x0, y0}, {x1, y0});  // Top
  DrawLine({x1, y0}, {x1, y1});  // Right
  DrawLine({x1, y1}, {x0, y1});  // Bottom
  DrawLine({x0, y1}, {x0, y0});  // Left
}
}  // namespace vs