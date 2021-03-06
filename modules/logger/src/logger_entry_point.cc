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

#include <iostream>
#include <string>

#include "vscge/logger/tee.h"

int main() {
  vs::Logger::Tee tee("log.txt");
  std::string message;
  while (true) {
    std::getline(std::cin, message);
    if (message.size()) {
      // TODO(Victor): add colored output to console.
      tee << message << '\n';
    } else {
      break;
    }
  }

  return 0;
}