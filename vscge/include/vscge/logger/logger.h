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

#include <string>

#include "vscge/core/core.h"

namespace vs {
// TODO(Victor): See if it makes sense for Logger to be a static class, if not,
// change the namespace to be lower case.
namespace Logger {
enum class Level {
  kInfo,
  kError,
  kDebug,
};
void VS_API Initialize();
// TODO(Victor): Maybe also specify a logging file?
void VS_API Log(std::string_view message, Level level = Level::kInfo);
}  // namespace Logger
}  // namespace vs

#endif  // VSCGE_INCLUDE_VSCGE_LOGGER_LOGGER_H_
