#include "vscge/core/application.h"

#include <Windows.h>

#include <algorithm>
#include <string>
#include <thread>
#include <vector>

#include "vscge/core/consts.h"
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

  std::thread game_loop(&Application::MainLoop, this);
  game_loop.join();
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

    DWORD num_events;
    GetNumberOfConsoleInputEvents(buffer_in_, &num_events);

    INPUT_RECORD event_buffer[32];  // NOLINT
    ReadConsoleInput(buffer_in_, event_buffer, num_events,
                     &num_events);  // NOLINT
    for (int i = 0; i < num_events; ++i) {
      auto event = event_buffer[i];
      switch (event.EventType) {
        case KEY_EVENT: {
          KEY_EVENT_RECORD record = event.Event.KeyEvent;
          KeyEvent event = {(bool)record.bKeyDown, (vs::Key)record.wVirtualKeyCode};
          OnEvent(event);

          break;
        }
        case MOUSE_EVENT: {
          MOUSE_EVENT_RECORD record = event.Event.MouseEvent;
          MouseButton button =
              (record.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
                  ? MouseButton::kLeft
                  : MouseButton::kRight;
          MouseEvent event = {(int)record.dwMousePosition.X,
                              (int)record.dwMousePosition.Y, button};
          OnEvent(event);

          break;
        }
        case WINDOW_BUFFER_SIZE_EVENT: {
          WINDOW_BUFFER_SIZE_RECORD record = event.Event.WindowBufferSizeEvent;
        }
        case MENU_EVENT: {
          MENU_EVENT_RECORD record = event.Event.MenuEvent;
        }
        case FOCUS_EVENT: {
          FOCUS_EVENT_RECORD record = event.Event.FocusEvent;
        }
      }
    }

    OnUpdate(timestep);

    Renderer::Render();
  }
}
}  // namespace vs
