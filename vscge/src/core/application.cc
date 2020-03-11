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
#include <vector>

#include "vscge/core/timer.h"
#include "vscge/event/event.h"
#include "vscge/event/key_event.h"
#include "vscge/event/mouse_event.h"
#include "vscge/instrumentation/profiler.h"
#include "vscge/logger/logger.h"
#include "vscge/utils/conversions.h"

namespace vs {
Application::Application(const Size &screen_size, const Size &font_size)
    : buffer_in_(GetStdHandle(STD_INPUT_HANDLE)) {
  SetConsoleMode(buffer_in_, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT |
                                 ENABLE_MOUSE_INPUT);

  Renderer::Initialize(GetStdHandle(STD_OUTPUT_HANDLE), screen_size, font_size);
  Logger::Initialize();

  SetConsoleCtrlHandler(
      static_cast<PHANDLER_ROUTINE>(Application::CloseHandler), true);

  is_running_ = true;
}

BOOL Application::CloseHandler(DWORD ctrl_event) {
  Logger::Log("Stopping application!");
  is_running_ = false;
  std::unique_lock lock(closing_);
  has_finished_.wait(lock);
  return true;
}

void Application::Start() {
  VS_PROFILE_BEGIN_SESSION("Start", "runtime.json");
  OnStart();

  std::thread game_loop(VS_BIND_THREAD(Application::MainLoop));
  std::thread event_loop(VS_BIND_THREAD(Application::EventListener));
  game_loop.join();
  event_loop.join();
  VS_PROFILE_END_SESSION();

  has_finished_.notify_all();
}

void Application::MainLoop() {
  Stopwatch timer;
  timer.Start();
  while (is_running_) {
    VS_PROFILE_FUNCTION();
    Timestep timestep = timer.Stop();
    std::string timing_message =
        "Timestep: " + std::to_string(timestep.Milliseconds()) +
        " ms | FPS: " + std::to_string(static_cast<int>(1 / timestep));
    Logger::Log(timing_message, Logger::Level::kCore);

    timer.Start();

    OnUpdate(timestep);

    Renderer::Render();
  }
}

// TODO(Victor): Move to a platform layer.
void Application::EventListener() {
  Ref<MouseEvent> previous_mouse_event;
  std::unordered_map<Key, Ref<KeyEvent>> previous_key_event;
  while (is_running_) {
    DWORD num_events;
    GetNumberOfConsoleInputEvents(buffer_in_, &num_events);

    constexpr size_t kMaxEvents = 32;
    std::array<INPUT_RECORD, kMaxEvents> event_buffer = {};
    ReadConsoleInput(buffer_in_, event_buffer.data(), num_events, &num_events);
    for (size_t i = 0; i < num_events; ++i) {
      auto read_event = event_buffer.at(i);
      switch (read_event.EventType) {
        case KEY_EVENT: {
          VS_PROFILE_SCOPE("KEY_EVENT");
          KEY_EVENT_RECORD record = read_event.Event.KeyEvent;  // NOLINT
          Key key = static_cast<Key>(record.wVirtualKeyCode);
          bool is_down = record.bKeyDown;

          // INFO(Victor): for some reason, this can't be an std::string_view,
          // should investigate more.
          std::string message = "Received key " +
                                std::to_string(static_cast<int>(key)) + ' ' +
                                (is_down ? "down" : "up");
          Logger::Log(message, Logger::Level::kCore);

          // If first time, create a dummy KeyReleasedEvent
          if (!previous_key_event[key]) {
            previous_key_event[key] =
                CreateRef<KeyReleasedEvent>(KeyReleasedEvent{key});
          }

          message = "Previous state: " + previous_key_event[key]->TypeName();
          Logger::Log(message, Logger::Level::kCore);

          if (previous_key_event[key]->Type() != EventType::kKeyReleased &&
              !is_down) {
            KeyReleasedEvent event{key};
            previous_key_event[key] = CreateRef<KeyReleasedEvent>(event);
          } else if (previous_key_event[key]->Type() ==
                         EventType::kKeyReleased &&
                     is_down) {
            KeyPressedEvent event{key};
            previous_key_event[key] = CreateRef<KeyPressedEvent>(event);
          } else {
            // TODO(Victor): Add an event KeyHold.
            previous_key_event[key] = CreateRef<KeyEvent>(KeyEvent{key});
          }

          OnEvent(previous_key_event[key]);

          break;
        }
        case MOUSE_EVENT: {
          VS_PROFILE_SCOPE("MOUSE_EVENT");
          MOUSE_EVENT_RECORD record = read_event.Event.MouseEvent;  // NOLINT
          Point position = record.dwMousePosition;
          MouseButtons buttons;

          if (record.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) {
            buttons.left = true;
          }
          if (record.dwButtonState & RIGHTMOST_BUTTON_PRESSED) {
            buttons.right = true;
          }

          // If first time, create a dummy MouseEvent
          if (!previous_mouse_event) {
            previous_mouse_event =
                CreateRef<MouseEvent>(MouseEvent{{0, 0}, {false, false}});
          }

          // TODO(Victor): The logic to get button presses/releases is mostly
          // certainly wrong.
          if (record.dwEventFlags & MOUSE_MOVED) {
            // NOLINTNEXTLINE
            MouseMovedEvent event = {previous_mouse_event->position, position,
                                     buttons};
            previous_mouse_event = CreateRef<MouseMovedEvent>(event);
          } else {
            if ((previous_mouse_event->buttons.left && !buttons.left) ||
                (previous_mouse_event->buttons.right && !buttons.right)) {
              MouseButtonReleasedEvent event = {position, buttons};
              previous_mouse_event = CreateRef<MouseButtonReleasedEvent>(event);
            } else if ((!previous_mouse_event->buttons.left && buttons.left) ||
                       (!previous_mouse_event->buttons.right &&
                        buttons.right)) {
              MouseButtonPressedEvent event = {position, buttons};
              previous_mouse_event = CreateRef<MouseButtonPressedEvent>(event);
            }
          }

          OnEvent(previous_mouse_event);

          break;
        }
        case WINDOW_BUFFER_SIZE_EVENT:
        case MENU_EVENT:
        case FOCUS_EVENT:
          break;
      }
    }
  }
}
}  // namespace vs
