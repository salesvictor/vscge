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

#ifndef VSCGE_INCLUDE_VSCGE_CORE_APPLICATION_H_
#define VSCGE_INCLUDE_VSCGE_CORE_APPLICATION_H_

#include <Windows.h>

#include <atomic>
#include <condition_variable>
#include <vector>

#include "vscge/api.h"
#include "vscge/core/timer.h"
#include "vscge/core/types.h"
#include "vscge/core/window.h"
#include "vscge/event/event.h"
#include "vscge/graphics/renderer.h"
#include "vscge/logger/logger.h"
#include "vscge/memory/reference.h"

namespace vs {
class VS_API Application {
 public:
  explicit Application(const Size& screen_size = {800, 600},
                       const Size& pixel_size  = {1, 1});

  void Initialize();

 protected:
  virtual void OnStart() {}
  virtual void OnEvent(Ref<Event>) {}
  virtual void OnUpdate(const Timestep&) = 0;

  void Log(std::string_view message, Logger::Level level);

  virtual ~Application() = default;

 private:
  void MainLoop();
  Window window_;

  Logger logger_;
  Renderer renderer_;
};
}  // namespace vs

#endif  // VSCGE_INCLUDE_VSCGE_CORE_APPLICATION_H_
