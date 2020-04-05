// Copyright 2020 Victor Sales
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "vscge/core/window.h"

#include <Windows.h>

#include <unordered_map>

#include "vscge/event/event.h"
#include "vscge/instrumentation/profiler.h"
#include "vscge/logger/logger.h"

namespace vs {
struct Internals {
  HANDLE buffer_in{GetStdHandle(STD_INPUT_HANDLE)};
};

Internals internals;

BOOL CloseHandler(DWORD) {
  Logger::Log("Stopping application!");
  Window::is_running_ = false;
  std::unique_lock lock(Window::closing_);
  Window::has_finished_.wait(lock);
  return true;
}

void Window::Initialize() {
  SetConsoleMode(internals.buffer_in, ENABLE_EXTENDED_FLAGS |
                                          ENABLE_WINDOW_INPUT |
                                          ENABLE_MOUSE_INPUT);
  SetConsoleCtrlHandler(static_cast<PHANDLER_ROUTINE>(CloseHandler), true);
  Window::is_running_ = true;
}

void Window::InputHandler() {
  Ref<MouseEvent> previous_mouse_event;
  std::unordered_map<Key, Ref<KeyEvent>> previous_key_event;
  while (Window::is_running_) {
    DWORD num_events;
    GetNumberOfConsoleInputEvents(internals.buffer_in, &num_events);

    constexpr size_t kMaxEvents = 32;

    std::array<INPUT_RECORD, kMaxEvents> event_buffer{};
    ReadConsoleInput(internals.buffer_in, event_buffer.data(), num_events,
                     &num_events);
    for (size_t i = 0; i < num_events; ++i) {
      auto read_event = event_buffer.at(i);
      switch (read_event.EventType) {
        case KEY_EVENT: {
          VS_PROFILE_SCOPE("KEY_EVENT");
          KEY_EVENT_RECORD record = read_event.Event.KeyEvent;  // NOLINT

          Key key      = static_cast<Key>(record.wVirtualKeyCode);
          bool is_down = record.bKeyDown;

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
          Point position = {record.dwMousePosition.X, record.dwMousePosition.Y};
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
            previous_mouse_event  = CreateRef<MouseMovedEvent>(event);
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