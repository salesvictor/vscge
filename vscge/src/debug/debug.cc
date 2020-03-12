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

#include "vscge/debug/debug.h"

#include <string>

#include "vscge/logger/logger.h"

namespace vs::debug {
bool Fail(std::string cond_str, std::string function, std::string line,
          std::string file) {
  std::string message = "Failed assertion " + cond_str + " in " + function +
                        ", line " + line + ", at " + file;
  Logger::Log(message, Logger::Level::kError);
  *((int*)0) = 0;  // NOLINT: The point is to break here.

  return false;
}
}  // namespace vs::debug
