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
#include <unordered_map>

#include "vscge/api.h"

namespace vs {
class VS_API Logger {
 public:
  enum class Level {
    kInfo,
    kError,
    kDebug,
    kCore,
  };
  void Initialize();
  bool IsInitialized();
  // TODO(Victor): Maybe also specify a logging file?
  void Log(std::string_view message, Level level = Level::kInfo);

 private:
  bool is_initialized_ = false;
};

inline std::unordered_map<Logger::Level, std::string_view>
    logger_level_str_map = {
        {Logger::Level::kInfo, "Info "},
        {Logger::Level::kError, "Error"},
        {Logger::Level::kDebug, "Debug"},
        {Logger::Level::kCore, "Core "},
};
}  // namespace vs

#endif  // VSCGE_INCLUDE_VSCGE_LOGGER_LOGGER_H_
