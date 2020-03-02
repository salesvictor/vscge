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
    std::wstring title = std::wstring(L"VS CGE - FPS: ") +
                         std::to_wstring(static_cast<int>(1 / timestep));
    SetConsoleTitle(title.c_str());

    timer.Start();

    OnUpdate(timestep);

    Renderer::Render();
  }
}

void Application::EventListener() {
  constexpr size_t kMaxEvents = 32;
  while (true) {
    DWORD num_events;
    GetNumberOfConsoleInputEvents(buffer_in_, &num_events);

    std::array<INPUT_RECORD, kMaxEvents> event_buffer;
    ReadConsoleInput(buffer_in_, event_buffer.data(), num_events, &num_events);
    for (size_t i = 0; i < num_events; ++i) {
      auto event = event_buffer.at(i);
      switch (event.EventType) {
        case KEY_EVENT: {
          KEY_EVENT_RECORD record = event.Event.KeyEvent;
          KeyEvent event = {static_cast<bool>(record.bKeyDown),
                            static_cast<vs::Key>(record.wVirtualKeyCode)};
          OnEvent(CreateRef<KeyEvent>(event));

          break;
        }
        case MOUSE_EVENT: {
          MOUSE_EVENT_RECORD record = event.Event.MouseEvent;
          MouseButton button =
              (record.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
                  ? MouseButton::kLeft
                  : MouseButton::kRight;
          MouseEvent event = {static_cast<int>(record.dwMousePosition.X),
                              static_cast<int>(record.dwMousePosition.Y),
                              button};
          OnEvent(CreateRef<MouseEvent>(event));

          break;
        }
        case WINDOW_BUFFER_SIZE_EVENT: {
          WINDOW_BUFFER_SIZE_RECORD record = event.Event.WindowBufferSizeEvent;

          break;
        }
        case MENU_EVENT: {
          MENU_EVENT_RECORD record = event.Event.MenuEvent;

          break;
        }
        case FOCUS_EVENT: {
          FOCUS_EVENT_RECORD record = event.Event.FocusEvent;

          break;
        }
      }
    }
  }
}
}  // namespace vs
