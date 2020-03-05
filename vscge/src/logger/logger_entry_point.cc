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

#include <Windows.h>

int main() {
  HANDLE input = GetStdHandle(STD_INPUT_HANDLE);
  HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);

  constexpr size_t buffer_size = 1000;
  char buffer[buffer_size];
  while (true) {
    DWORD read = 0;
    ReadFile(input, buffer, buffer_size, &read, NULL);
    if (read) {
      DWORD written = 0;
      WriteFile(output, buffer, read, &written, NULL);
    }
  }

  return 0;
}