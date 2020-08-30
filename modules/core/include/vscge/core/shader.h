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
#include <type_traits>

#include "vscge/api.h"
#include "vscge/core/short_types.h"
#include "vscge/math/matrix.h"
#include "vscge/math/vector.h"

namespace vs {
class VS_API Shader {
 public:
  Shader(std::string_view vertex_shader_path   = "",
         std::string_view fragment_shader_path = "");

  void Use();

  // Uniforms by name
  void SetUniformMatrix4fv(std::string_view name, const Mat4& mat);
  void SetUniform4fv(std::string_view name, const Vec4& mat);
  void SetUniform3fv(std::string_view name, const Vec3& vec);
  void SetUniform2fv(std::string_view name, const Vec2& vec);
  void SetUniform1f(std::string_view name, float val);

  // Uniforms by layout location
  void SetUniformMatrix4fv(std::size_t loc, const Mat4& mat);
  void SetUniform4fv(std::size_t loc, const Vec4& mat);
  void SetUniform3fv(std::size_t loc, const Vec3& vec);
  void SetUniform2fv(std::size_t loc, const Vec2& vec);
  void SetUniform1f(std::size_t loc, float val);

  // Generic interfaces
  template <typename T>
  void SetUniform(std::string_view name, const T& val) {
    if constexpr (std::is_same_v<T, Mat4>) {
      SetUniformMatrix4fv(name, val);
    } else if constexpr (std::is_same_v<T, Vec4>) {
      SetUniform4fv(name, val);
    } else if constexpr (std::is_same_v<T, Vec3>) {
      SetUniform3fv(name, val);
    } else if constexpr (std::is_same_v<T, Vec2>) {
      SetUniform2fv(name, val);
    } else if constexpr (std::is_same_v<T, float>) {
      SetUniform1f(name, val);
    } else {
      static_assert(false, "Not a known type!");
    }
  }
  template <typename T>
  void SetUniform(std::size_t loc, const T& val) {
    if constexpr (std::is_same_v<T, Mat4>) {
      SetUniformMatrix4fv(loc, val);
    } else if constexpr (std::is_same_v<T, Vec4>) {
      SetUniform4fv(loc, val);
    } else if constexpr (std::is_same_v<T, Vec3>) {
      SetUniform3fv(loc, val);
    } else if constexpr (std::is_same_v<T, Vec2>) {
      SetUniform2fv(loc, val);
    } else if constexpr (std::is_same_v<T, float>) {
      SetUniform1f(loc, val);
    } else {
      static_assert(false, "Not a known type!");
    }
  }

 private:
  uint id_;
};
}  // namespace vs

#endif  // VSCGE_INCLUDE_VSCGE_CORE_SHADER_H_
