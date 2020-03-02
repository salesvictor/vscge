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

#include <vector>

#include "vscge/core/core.h"
#include "vscge/core/renderer.h"
#include "vscge/core/timer.h"
#include "vscge/core/types.h"
#include "vscge/event/event.h"

namespace vs {
class VS_API Application {
 public:
  Application(const Size &screen_size = {240, 120},
              const Size &font_size = {4, 4});

  void Start();

 private:
  void MainLoop();
  void EventListener();

  virtual void OnStart() {}
  virtual void OnEvent(Ref<Event> event) {}
  virtual void OnUpdate(const Timestep &timestep) = 0;

  HANDLE buffer_in_;
};
}  // namespace vs

#endif  // VSCGE_INCLUDE_VSCGE_CORE_APPLICATION_H_
