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

#include "vscge/graphics/vertex_array.h"

#include <gl/gl3w.h>

#include <vector>

#include "vscge/debug/debug.h"
#include "vscge/memory/reference.h"

namespace vs {
VertexArray::VertexArray() { glCreateVertexArrays(1, &id_); }
VertexArray::~VertexArray() { glDeleteVertexArrays(1, &id_); }

void VertexArray::Bind() const { glBindVertexArray(id_); }
void VertexArray::Unbind() const { glBindVertexArray(0); }

int DataTypeToGL(DataType type) {
  switch (type) {
    case DataType::kFloat:
    case DataType::kFloat2:
    case DataType::kFloat3:
    case DataType::kFloat4: {
      return GL_FLOAT;
    }

    case DataType::kInt:
    case DataType::kInt2:
    case DataType::kInt3:
    case DataType::kInt4: {
      return GL_INT;
    }

    case DataType::kBool:
    case DataType::kBool2:
    case DataType::kBool3:
    case DataType::kBool4: {
      return GL_BOOL;
    }
    default: {
      VS_ASSERT(false);
      return 0;
    }
  }
}

void VertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vbo) {
  VS_ASSERT(vbo->layout().Attribs().size());

  Bind();
  vbo->Bind();

  const auto& layout = vbo->layout();

  int index                = 0;
  VertexAttrib prev_attrib = {DataType::kNull};
  for (const auto& attrib : layout) {
    glVertexAttribPointer(index, DataTypeElemCount(attrib.type),
                          DataTypeToGL(attrib.type),
                          attrib.should_normalize ? GL_TRUE : GL_FALSE,
                          (GLsizei)layout.ByteSize(), (void*)prev_attrib.ByteSize());
    glEnableVertexAttribArray(index);
    prev_attrib = attrib;
    index++;
  }
  vertex_buffers_.push_back(vbo);
}
void VertexArray::SetIndexBuffer(const Ref<IndexBuffer>& ibo) {
  Bind();
  ibo->Bind();
  index_buffer_ = ibo;
}
}  // namespace vs
