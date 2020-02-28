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
    : buffer_in_(GetStdHandle(STD_INPUT_HANDLE)) {
  buffer_in_ = GetStdHandle(STD_INPUT_HANDLE);
  SetConsoleMode(buffer_in_, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT |
                                 ENABLE_MOUSE_INPUT);
  Renderer::Initialize(GetStdHandle(STD_OUTPUT_HANDLE), screen_size, font_size);
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
    SetConsoleTitle(title.c_str());

    timer.Start();

    OnUpdate(timestep);

    Renderer::Render();
  }
}
}  // namespace vs