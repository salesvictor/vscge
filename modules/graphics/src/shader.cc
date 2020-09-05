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

#include "vscge/graphics/shader.h"

#include <gl/gl3w.h>

#include <fstream>
#include <sstream>
#include <string>
#include <string_view>

#include "vscge/core/short_types.h"
#include "vscge/math/transform.h"

namespace vs {

constexpr const char vertex_shader_default[] = R"#(
#version 330 core
layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vColor;
layout (location = 2) in vec2 vTex;

out vec3 fColor;
out vec2 fTex;

// Defaults to identity if not set.
uniform mat4 vTransform;

void main()
{
  gl_Position = vTransform * vec4(vPos, 1.0f);

  vec3 color = vColor;
  if (color == vec3(-1.0f, -1.0f, -1.0f)) {
    color = vec3(0.53f, 0.12f, 0.47f);
  }
  fColor = color;
  fTex   = vTex;
}
)#";

constexpr const char fragment_shader_default[] = R"#(
#version 330 core
in vec3 fColor;

out vec4 FragColor;

void main()
{
  FragColor = vec4(fColor, 1.0f);
} 
)#";

enum class ShaderType {
  kVertex,
  kFragment,
};

unsigned int CreateAndCompileShader(std::string_view shader_src,
                                    ShaderType shader_type) {
  auto type = shader_type == ShaderType::kVertex ? GL_VERTEX_SHADER
                                                 : GL_FRAGMENT_SHADER;
  uint id         = glCreateShader(type);
  auto shader_str = shader_src.data();
  glShaderSource(id, 1, &shader_str, NULL);
  glCompileShader(id);

  // Error checking
  int success;
  glGetShaderiv(id, GL_COMPILE_STATUS, &success);
  if (!success) {
    int info_log_size;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &info_log_size);

    std::string info_log;
    info_log.reserve(info_log_size);
    glGetShaderInfoLog(id, info_log_size, NULL, info_log.data());
    exit(1);
  }

  return id;
}

Shader::Shader(std::string_view name, std::string_view vertex_shader_path,
               std::string_view fragment_shader_path) : name_{name} {
  std::string vertex_shader;
  std::string fragment_shader;

  // If paths not set, use the default shaders.
  // If set, load them.
  if (vertex_shader_path.empty()) {
    vertex_shader = vertex_shader_default;
  } else {
    std::ifstream vertex_file{vertex_shader_path.data()};
    std::ostringstream ss;
    ss << vertex_file.rdbuf();
    vertex_shader = ss.str();
  }

  if (fragment_shader_path.empty()) {
    fragment_shader = fragment_shader_default;
  } else {
    std::ifstream fragment_file{fragment_shader_path.data()};
    std::ostringstream ss;
    ss << fragment_file.rdbuf();
    fragment_shader = ss.str();
  }

  // Shaders compilation
  uint vertex_shader_id{
      CreateAndCompileShader(vertex_shader, ShaderType::kVertex)};
  uint fragment_shader_id{
      CreateAndCompileShader(fragment_shader, ShaderType::kFragment)};

  // Linking
  id_ = glCreateProgram();
  glAttachShader(id_, vertex_shader_id);
  glAttachShader(id_, fragment_shader_id);
  glLinkProgram(id_);

  // Error checking
  int success;
  glGetProgramiv(id_, GL_LINK_STATUS, &success);
  if (!success) {
    int info_log_size;
    glGetProgramiv(id_, GL_INFO_LOG_LENGTH, &info_log_size);

    std::string info_log;
    info_log.reserve(info_log_size);
    glGetProgramInfoLog(id_, info_log_size, NULL, info_log.data());
    exit(1);
  }

  // Clean-up
  glDeleteShader(vertex_shader_id);
  glDeleteShader(fragment_shader_id);

  // Defaults vTransform to identity if vertex shader was the default
  if (vertex_shader_path.empty()) {
    SetUniform("vTransform", IdMat4());
  }
}

void Shader::Use() { glUseProgram(id_); }

void Shader::SetUniformMatrix4fv(std::string_view name, const Mat4& mat) {
  auto loc = glGetUniformLocation(id_, name.data());
  SetUniformMatrix4fv(loc, mat);
}
void Shader::SetUniform4fv(std::string_view name, const Vec4& vec) {
  auto loc = glGetUniformLocation(id_, name.data());
  SetUniform4fv(loc, vec);
}
void Shader::SetUniform3fv(std::string_view name, const Vec3& vec) {
  auto loc = glGetUniformLocation(id_, name.data());
  SetUniform3fv(loc, vec);
}
void Shader::SetUniform2fv(std::string_view name, const Vec2& vec) {
  auto loc = glGetUniformLocation(id_, name.data());
  SetUniform2fv(loc, vec);
}
void Shader::SetUniform1f(std::string_view name, float val) {
  auto loc = glGetUniformLocation(id_, name.data());
  SetUniform1f(loc, val);
}

void Shader::SetUniformMatrix4fv(std::size_t loc, const Mat4& mat) {
  glProgramUniformMatrix4fv(id_, static_cast<int>(loc), 1, GL_FALSE,
                            mat.Buffer());
}
void Shader::SetUniform4fv(std::size_t loc, const Vec4& vec) {
  glProgramUniform4fv(id_, static_cast<int>(loc), 1, vec.Buffer());
}
void Shader::SetUniform3fv(std::size_t loc, const Vec3& vec) {
  glProgramUniform3fv(id_, static_cast<int>(loc), 1, vec.Buffer());
}
void Shader::SetUniform2fv(std::size_t loc, const Vec2& vec) {
  glProgramUniform2fv(id_, static_cast<int>(loc), 1, vec.Buffer());
}
void Shader::SetUniform1f(std::size_t loc, float val) {
  glProgramUniform1f(id_, static_cast<int>(loc), val);
}
}  // namespace vs
