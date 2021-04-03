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

// #include "vscge/logger/logger.h"
#include "vscge/util/macro.h"

LRESULT CALLBACK WindowProc(HWND window_handle, UINT message_code,
                            WPARAM w_param, LPARAM l_param) {
  if (message_code == WM_DESTROY) {
    // vs::Logger::Log("Stopping application!");
    vs::Window::is_running_ = false;
    std::unique_lock lock(vs::Window::closing_);
    vs::Window::has_finished_.wait(lock);
    PostQuitMessage(0);
    return 0;
  }
  return DefWindowProc(window_handle, message_code, w_param, l_param);
}

namespace vs {
void Window::Initialize(const Size& screen_size) {
  // TODO(Victor): The way Windows works is that the message queue is thread
  // dependant, that means that the thread that creates the window is the one
  // that receives its messages.
  //
  // That means that we have to create the window in the same thread as the
  // InputHandler, should think of a better way to do this...
  size_ = screen_size;
  std::thread input_loop(VS_BIND_THREAD(Window::InputHandler));
  input_loop.detach();

  Window::is_running_ = true;
}

void Window::InputHandler() {
  constexpr char window_class_name[] = "Application"; // NOLINT

  HINSTANCE instance = GetModuleHandle(nullptr);

  WNDCLASSEXA window_class{};
  window_class.cbSize        = sizeof(WNDCLASSEXA);
  window_class.style         = CS_VREDRAW | CS_HREDRAW;
  window_class.lpfnWndProc   = WindowProc;
  window_class.hInstance     = instance;
  window_class.lpszClassName = window_class_name;
  window_class.hCursor       = LoadCursor(NULL, IDC_ARROW);

  STARTUPINFOA startup_info{};
  GetStartupInfoA(&startup_info);

  int show_flags = startup_info.wShowWindow;

  RegisterClassExA(&window_class);
  handle_ = CreateWindowExA(0, window_class_name, "VSCGE", WS_OVERLAPPEDWINDOW,
                            CW_USEDEFAULT, CW_USEDEFAULT, size_.width,
                            size_.height, nullptr, nullptr, instance, nullptr);
  ShowWindow(static_cast<HWND>(handle_), show_flags);
  ShowCursor(true);
  is_initialized_ = true;
  MSG message;
  
  // TODO(Victor): Look at PeekMessage() instead of GetMessage(),
  // it might solve the weird initialization problem :)
  while (GetMessage(&message, nullptr, 0, 0)) {
    TranslateMessage(&message);
    DispatchMessage(&message);
  }
}
}  // namespace vs
