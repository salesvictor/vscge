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

#include <Windows.h>

LRESULT CALLBACK WindowProc(HWND window_handle, UINT message_code,
                            WPARAM w_param, LPARAM l_param) {
  return DefWindowProc(window_handle, message_code, w_param, l_param);
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE not_used, PSTR args,
                   int show_flags) {
  constexpr char window_class_name[] = "Application";

  WNDCLASSEXA window_class   = {};
  window_class.cbSize        = sizeof(WNDCLASSEXA);
  window_class.style         = CS_VREDRAW | CS_HREDRAW;
  window_class.lpfnWndProc   = WindowProc;
  window_class.hInstance     = instance;
  window_class.lpszClassName = window_class_name;

  RegisterClassExA(&window_class);
  HWND window_handle =
      CreateWindowExA(0, window_class_name, "VSCGE", WS_OVERLAPPEDWINDOW,
                      CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                      CW_USEDEFAULT, nullptr, nullptr, instance, nullptr);
  ShowWindow(window_handle, show_flags);

  MSG message;
  while (GetMessage(&message, nullptr, 0, 0)) {
    TranslateMessage(&message);
    DispatchMessage(&message);
  }
  return 0;
}
