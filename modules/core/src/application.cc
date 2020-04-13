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

namespace vs {
Application::Application(const Size& screen_size, const Size& pixel_size) {
  window_.Initialize(screen_size);
  while (!window_.is_initialized_) continue;
  renderer_.Initialize(window_, pixel_size);
  logger_.Initialize();
}

void Application::Initialize() {
  VS_PROFILE_BEGIN_SESSION("Start", "runtime.json");
  OnStart();
  MainLoop();
  VS_PROFILE_END_SESSION();

  platform::Window::has_finished_.notify_all();
}

void Application::MainLoop() {
  Stopwatch timer;
  timer.Start();
  while (platform::Window::is_running_) {
    VS_PROFILE_FUNCTION();
    Timestep timestep = timer.Stop();
    std::string timing_message =
        "Timestep: " + std::to_string(timestep.Milliseconds()) +
        " ms | FPS: " + std::to_string(static_cast<int>(1 / timestep));
    logger_.Log(timing_message, platform::Logger::Level::kCore);

    timer.Start();

    OnUpdate(timestep);

    renderer_.Render();
  }
}
}  // namespace vs
