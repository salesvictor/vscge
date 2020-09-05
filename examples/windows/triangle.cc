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
      // Pos               // Col
      -0.5f, -0.5f, 0.0f,  0.0f,  0.0f,  0.0f,
       0.5f, -0.5f, 0.0f,  0.0f,  0.0f,  0.0f,
       0.0f,  0.5f, 0.0f,  0.0f,  0.0f,  0.0f,
      -1.0f, -0.5f, 0.0f,  0.5f,  0.0f,  0.0f,
       1.0f,  0.8f, 0.0f, -1.0f, -1.0f, -1.0f,
       0.8f,  1.0f, 0.0f, -1.0f, -1.0f, -1.0f,
    };
    // clang-format on

    auto vbo = vs::VertexBuffer::Make(vertices_);

    vs::VertexLayout layout = {
        {vs::DataType::kVec3, "vPos"},
        {vs::DataType::kVec3, "vColor"},
    };
    vbo->layout() = layout;

    auto ibo = vs::IndexBuffer::Make({0, 1, 2, 3, 4, 5});
    vao_.AddVertexBuffer(vbo);
    vao_.SetIndexBuffer(ibo);

    vao_.Unbind();
    vbo->Unbind();
    ibo->Unbind();
  }

  void OnUpdate(const vs::Timestep&) override {
    glClearColor(0.1f, 0.1f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // glBindVertexArray(vao_);
    vao_.Bind();
    shader_.Use();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  }

  vs::VertexArray vao_{};
  vs::Shader shader_{};
  std::vector<float> vertices_;
};

VS_REGISTER_APP(Triangle);
