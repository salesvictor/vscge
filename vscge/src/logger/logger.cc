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

namespace vs::Logger {
struct Internals {
  HANDLE write_handle;
  std::unordered_map<Level, std::string_view> level_map = {
      {Level::kInfo, "Info"},
      {Level::kError, "Error"},
      {Level::kDebug, "Debug"}};
};

Internals internals;

void Initialize() {
  HANDLE logger_in_read;
  HANDLE logger_in_write;

  SECURITY_ATTRIBUTES sa = {
      .nLength = sizeof(SECURITY_ATTRIBUTES),
      .bInheritHandle = TRUE,
  };
  CreatePipe(&logger_in_read, &logger_in_write, &sa, 0);
  SetHandleInformation(logger_in_write, HANDLE_FLAG_INHERIT, 0);
  STARTUPINFOA si = {
      .cb = sizeof(STARTUPINFOA),
      .lpTitle = "Logger",
      .dwX = 0,
      .dwY = 0,
      .dwFlags =
          STARTF_USEPOSITION | STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW,
      .wShowWindow = SW_SHOWNOACTIVATE,
      .hStdInput = logger_in_read,
  };
  PROCESS_INFORMATION pi = {};
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
}

void Log(std::string_view message, Level level) {
  // Unfortunately, Windows pushes the Ex API by saying the previous one could
  // be deprecated.
  constexpr std::wstring_view date_format = L"ddMMMyyyy";
  constexpr std::wstring_view time_format = L"HH':'mm':'ss";

  std::wstring wtime;
  wtime.reserve(time_format.size());
  GetTimeFormatEx(LOCALE_NAME_USER_DEFAULT, 0, nullptr, time_format.data(),
                  wtime.data(), wtime.capacity());
  std::wstring wdate;
  wdate.reserve(date_format.size());
  GetDateFormatEx(LOCALE_NAME_USER_DEFAULT, 0, nullptr, date_format.data(),
                  wdate.data(), wdate.capacity(), nullptr);

  // As we only get ASCII characters here, we do a dirty conversion.
  std::string date(wdate.begin(), wdate.end());
  std::string time(wtime.begin(), wtime.end());

  std::string timestamp = date + " " + time;
  std::string level_string = std::string(internals.level_map[level]);
  std::string write_message = "[" + date + " " + time + "|" + level_string +
                              "] " + std::string(message);

  // No idea this needs to exist, but fount it here:
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
  WriteFile(internals.write_handle, write_message.data(), write_message.size(),
            &written, nullptr);
}
}  // namespace vs::Logger
