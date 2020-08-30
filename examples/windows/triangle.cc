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
#include <gl/gl3w.h>
#include <vscge/vscge.h>

class Triangle : public vs::Application {
  void OnStart() override {
    // clang-format off
    float vertices[] = {
      -0.5f, -0.5f, 0.0f,
       0.5f, -0.5f, 0.0f,
       0.0f,  0.5f, 0.0f,
    };
    // clang-format on

    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    const char* vertex_shader_src = R"#(
      #version 330 core
      layout (location = 0) in vec3 aPos;

      void main()
      {
          gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
      }
    )#";

    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_src, NULL);
    glCompileShader(vertex_shader);

    int success;
    char info_log[512];
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
      Log(info_log, vs::Logger::Level::kError);
    }

    const char* fragment_shader_src = R"#(
      #version 330 core
      out vec4 FragColor;

      void main()
      {
          FragColor = vec4(0.53f, 0.12f, 0.47f, 1.0f);
      } 
    )#";

    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_src, NULL);
    glCompileShader(fragment_shader);

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
      Log(info_log, vs::Logger::Level::kError);
    }

    shader_program_ = glCreateProgram();
    glAttachShader(shader_program_, vertex_shader);
    glAttachShader(shader_program_, fragment_shader);
    glLinkProgram(shader_program_);

    glGetProgramiv(shader_program_, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(shader_program_, 512, NULL, info_log);
      Log(info_log, vs::Logger::Level::kError);
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
  }

  void OnUpdate(const vs::Timestep&) override {
    glClearColor(0.1f, 0.1f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shader_program_);
    glBindVertexArray(vao_);
    glDrawArrays(GL_TRIANGLES, 0, 3);
  }

  unsigned int vao_;
  unsigned int shader_program_;
};

VS_REGISTER_APP(Triangle);
