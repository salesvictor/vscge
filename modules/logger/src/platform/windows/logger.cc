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

#include "vscge/logger/logger.h"

#include <Windows.h>

#include <string>
#include <unordered_map>

#include "vscge/instrumentation/profiler.h"

namespace vs::platform::Logger {
struct Internals {
  bool initialized    = false;
  HANDLE write_handle = nullptr;

  std::unordered_map<Level, std::string_view> level_map = {
      {Level::kInfo, "Info "},
      {Level::kError, "Error"},
      {Level::kDebug, "Debug"},
      {Level::kCore, "Core "},
  };
};  // namespace vs::Logger

static Internals internals;

void Initialize() {
  VS_PROFILE_FUNCTION();
  HANDLE logger_in_read;
  HANDLE logger_in_write;

  SECURITY_ATTRIBUTES sa = {};
  sa.nLength             = sizeof(SECURITY_ATTRIBUTES);
  sa.bInheritHandle      = TRUE,

  CreatePipe(&logger_in_read, &logger_in_write, &sa, 0);
  SetHandleInformation(logger_in_write, HANDLE_FLAG_INHERIT, 0);
  STARTUPINFOA si = {};
  si.cb           = sizeof(STARTUPINFOA);
  si.lpTitle      = const_cast<char*>("Logger");  // NOLINT: C API...
  si.dwX          = 0;
  si.dwY          = 0;

  si.dwFlags = STARTF_USEPOSITION | STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;

  si.wShowWindow = SW_SHOWNOACTIVATE;
  si.hStdInput   = logger_in_read;

  PROCESS_INFORMATION pi     = {};
  std::string logger_command = "Logger.exe";

  CreateProcessA(nullptr, logger_command.data(), nullptr, nullptr, TRUE,
                 CREATE_NEW_CONSOLE, nullptr, nullptr, &si, &pi);
  CloseHandle(pi.hProcess);
  CloseHandle(pi.hThread);
  CloseHandle(logger_in_read);

  Sleep(200);  // NOLINT
  SetWindowPos(GetConsoleWindow(), HWND_TOP, 0, 0, 0, 0,
               SWP_NOMOVE | SWP_NOSIZE);

  internals.write_handle = logger_in_write;
  internals.initialized  = true;
}

bool IsInitialized() { return internals.initialized; }

void Log(std::string_view message, Level level) {
  VS_PROFILE_FUNCTION();
  // I could use the Ex API, but that means Unicode, and I didn't like it.
  constexpr std::string_view date_format = "ddMMMyyyy";
  constexpr std::string_view time_format = "HH':'mm':'ss";

  std::string time;
  time.resize(time_format.size() - 4);  // NOLINT: removing the '
  GetTimeFormatA(LOCALE_USER_DEFAULT, 0, nullptr, time_format.data(),
                 time.data(), static_cast<int>(time.capacity()));
  std::string date;
  date.resize(date_format.size());
  GetDateFormatA(LOCALE_USER_DEFAULT, 0, nullptr, date_format.data(),
                 date.data(), static_cast<int>(date.capacity()));

  std::string timestamp    = date + " " + time;
  std::string level_string = std::string(internals.level_map[level]);
  std::string write_message =
      "[" + timestamp + "|" + level_string + "] " + std::string(message) + '\n';

  // NOTE(Victor): No idea why this needs to exist, but fount it here:
  // https://stackoverflow.com/questions/28618715/c-writefile-unicode-characters
  //
  // The following is for handling Unicode.
  // int len =
  // WideCharToMultiByte(CP_UTF8, 0, write_message.c_str(),
  // write_message.length(), nullptr, 0, nullptr, nullptr);
  // std::string utf8_message;
  // utf8_message.resize(len);
  // WideCharToMultiByte(CP_UTF8, 0, write_message.c_str(),
  // write_message.length(), utf8_message.data(), len, nullptr, nullptr);

  DWORD written = 0;
  WriteFile(internals.write_handle, write_message.data(),
            static_cast<DWORD>(write_message.size()), &written, nullptr);
}
}  // namespace vs::platform::Logger
