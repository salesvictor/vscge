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
#include "vscge/logger/logger.h"
#include "vscge/utils/conversions.h"

namespace vs {
Application::Application(const Size &screen_size, const Size &font_size)
    : buffer_in_(GetStdHandle(STD_INPUT_HANDLE)) {
  SetConsoleMode(buffer_in_, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT |
                                 ENABLE_MOUSE_INPUT);
  Renderer::Initialize(GetStdHandle(STD_OUTPUT_HANDLE), screen_size, font_size);
  Logger::Initialize();
}

void Application::Start() {
  OnStart();

  std::thread game_loop(VS_BIND_THREAD(Application::MainLoop));
  std::thread event_loop(VS_BIND_THREAD(Application::EventListener));
  game_loop.join();
  event_loop.join();
}

void Application::MainLoop() {
  Timer timer;
  timer.Start();
  while (true) {
    Timestep timestep = timer.Stop();
    std::string title = std::string("VS CGE - FPS: ") +
                        std::to_string(static_cast<int>(1 / timestep));
    SetConsoleTitleA(title.c_str());

    timer.Start();

    OnUpdate(timestep);

    Renderer::Render();
  }
}

// TODO(Victor): Move to a platform layer.
void Application::EventListener() {
  Ref<MouseEvent> previous_mouse_event;
  std::unordered_map<Key, Ref<KeyEvent>> previous_key_event;
  while (true) {
    DWORD num_events;
    GetNumberOfConsoleInputEvents(buffer_in_, &num_events);

    constexpr size_t kMaxEvents = 32;
    std::array<INPUT_RECORD, kMaxEvents> event_buffer = {};
    ReadConsoleInput(buffer_in_, event_buffer.data(), num_events, &num_events);
    for (size_t i = 0; i < num_events; ++i) {
      auto read_event = event_buffer.at(i);
      switch (read_event.EventType) {
        case KEY_EVENT: {
          KEY_EVENT_RECORD record = read_event.Event.KeyEvent;
          Key key = static_cast<Key>(record.wVirtualKeyCode);
          bool is_down = record.bKeyDown;

          // If first time, create a dummy KeyEvent
          if (!previous_key_event[key]) {
            previous_key_event[key] = CreateRef<KeyEvent>(KeyEvent{key});
          }

          if (previous_key_event[key]->Type() == EventType::kKeyPressed &&
              !is_down) {
            KeyReleasedEvent event{key};
            previous_key_event[key] = CreateRef<KeyReleasedEvent>(event);
          } else if (previous_key_event[key]->Type() !=
                         EventType::kKeyPressed &&
                     is_down) {
            KeyPressedEvent event{key};
            previous_key_event[key] = CreateRef<KeyPressedEvent>(event);
          }

          OnEvent(previous_key_event[key]);

          break;
        }
        case MOUSE_EVENT: {
          MOUSE_EVENT_RECORD record = read_event.Event.MouseEvent;
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

          if (record.dwEventFlags & MOUSE_MOVED) {
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
        case WINDOW_BUFFER_SIZE_EVENT: {
          WINDOW_BUFFER_SIZE_RECORD record =
              read_event.Event.WindowBufferSizeEvent;

          break;
        }
        case MENU_EVENT: {
          MENU_EVENT_RECORD record = read_event.Event.MenuEvent;

          break;
        }
        case FOCUS_EVENT: {
          FOCUS_EVENT_RECORD record = read_event.Event.FocusEvent;

          break;
        }
      }
    }
  }
}
}  // namespace vs
