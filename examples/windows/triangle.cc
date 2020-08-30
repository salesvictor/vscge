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
    vertices_ = {
      {{-0.5f, -0.5f, 0.0f}, {{ 0.0f,  0.0f,  0.0f}}},
      {{ 0.5f, -0.5f, 0.0f}, {{ 0.0f,  0.0f,  0.0f}}},
      {{ 0.0f,  0.5f, 0.0f}, {{ 0.0f,  0.0f,  0.0f}}},
      {{-1.0f, -0.5f, 0.0f}, {{ 0.5f,  0.0f,  0.0f}}},
      {{ 1.0f,  0.8f, 0.0f}},
      {{ 0.8f,  1.0f, 0.0f}},
    };
    // clang-format on

    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    uint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(vs::Vertex),
                 vertices_.data(), GL_STATIC_DRAW);

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vs::Vertex),
                          (void*)0);
    glEnableVertexAttribArray(0);

    // Color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vs::Vertex),
                          (void*)(sizeof(vs::Vec3)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    vs::Shader shader{};
  }

  void OnUpdate(const vs::Timestep&) override {
    glClearColor(0.1f, 0.1f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindVertexArray(vao_);
    shader_.Use();
    glDrawArrays(GL_TRIANGLES, 0, (GLsizei)vertices_.size());
  }

  unsigned int vao_;
  vs::Shader shader_{};
  std::vector<vs::Vertex> vertices_;
};

VS_REGISTER_APP(Triangle);
