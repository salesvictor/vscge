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

#ifndef VSCGE_INCLUDE_VSCGE_CORE_SHADER_H_
#define VSCGE_INCLUDE_VSCGE_CORE_SHADER_H_

#include <string_view>

#include "vscge/api.h"
#include "vscge/core/short_types.h"

namespace vs {
class VS_API Shader {
 public:
  Shader(std::string_view vertex_shader_path   = "",
         std::string_view fragment_shader_path = "");

  void Use();

 private:
  uint id_;
};
}  // namespace vs

#endif  // VSCGE_INCLUDE_VSCGE_CORE_SHADER_H_
