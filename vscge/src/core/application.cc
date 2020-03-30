// Copyright 2020 Victor Sales
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "vscge/core/application.h"

#include <Windows.h>

#include <algorithm>
#include <array>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

#include "vscge/core/timer.h"
#include "vscge/event/event.h"
#include "vscge/instrumentation/profiler.h"
#include "vscge/logger/logger.h"
#include "vscge/util/macro.h"

// TODO(Victor): Remove this after fixing renderer.
#pragma warning(disable : 4100)

namespace vs {
Application::Application(const Size& screen_size, const Size& font_size) {
  window_.Initialize();
#if 0
  Renderer::Initialize(GetStdHandle(STD_OUTPUT_HANDLE), screen_size,
  font_size);
#endif
  Logger::Initialize();
}

void Application::Initialize() {
  VS_PROFILE_BEGIN_SESSION("Start", "runtime.json");
  OnStart();

  std::thread game_loop(VS_BIND_THREAD(Application::MainLoop));
  game_loop.join();
  VS_PROFILE_END_SESSION();

  Window::has_finished_.notify_all();
}

void Application::MainLoop() {
  Stopwatch timer;
  timer.Start();
  while (Window::is_running_) {
    VS_PROFILE_FUNCTION();
    Timestep timestep = timer.Stop();
    std::string timing_message =
        "Timestep: " + std::to_string(timestep.Milliseconds()) +
        " ms | FPS: " + std::to_string(static_cast<int>(1 / timestep));
    Logger::Log(timing_message, Logger::Level::kCore);

    timer.Start();

    OnUpdate(timestep);

    // Renderer::Render();
  }
}
}  // namespace vs
