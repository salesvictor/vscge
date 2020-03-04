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

#ifndef VSCGE_INCLUDE_VSCGE_LOGGER_LOGGER_H_
#define VSCGE_INCLUDE_VSCGE_LOGGER_LOGGER_H_

#include <Windows.h>

namespace vs {
namespace Logger {
void Initialize() {
  HANDLE logger_in_read;
  HANDLE logger_in_write;

  SECURITY_ATTRIBUTES sa = {
      .nLength = sizeof(SECURITY_ATTRIBUTES),
      .bInheritHandle = TRUE,
  };
  CreatePipe(&logger_in_read, &logger_in_write, &sa, 0);
  SetHandleInformation(logger_in_write, HANDLE_FLAG_INHERIT, 0);
  STARTUPINFO si = {
      .cb = sizeof(STARTUPINFO),
      .lpTitle = TEXT("Logger"),
      .dwX = 0,
      .dwY = 0,
      .dwFlags =
          STARTF_USEPOSITION | STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW,
      .wShowWindow = SW_SHOWNOACTIVATE,
      .hStdInput = logger_in_read,
  };
  PROCESS_INFORMATION pi = {};
  std::wstring logger_command = L"Logger.exe";
  CreateProcess(nullptr, logger_command.data(), nullptr, nullptr, TRUE,
                CREATE_NEW_CONSOLE, nullptr, nullptr, &si, &pi);
  CloseHandle(pi.hProcess);
  CloseHandle(pi.hThread);
  CloseHandle(logger_in_read);
  SetWindowPos(GetConsoleWindow(), HWND_TOPMOST, 0, 0, 0, 0,
               SWP_NOMOVE | SWP_NOSIZE);
}
}  // namespace Logger
}  // namespace vs

#endif  // VSCGE_INCLUDE_VSCGE_LOGGER_LOGGER_H_
