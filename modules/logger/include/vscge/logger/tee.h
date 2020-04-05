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

#ifndef VSCGE_INCLUDE_VSCGE_LOGGER_TEE_H_
#define VSCGE_INCLUDE_VSCGE_LOGGER_TEE_H_

#include <fstream>
#include <string>

#include "vscge/api.h"

namespace vs {
namespace Logger {
class VS_API Tee {
 public:
  explicit Tee(std::string_view filepath);
  ~Tee();

  template <typename Readable>
  Tee& operator<<(Readable message);

 private:
  std::ofstream file_;
};
}  // namespace Logger
}  // namespace vs

#endif  // VSCGE_INCLUDE_VSCGE_LOGGER_TEE_H_
