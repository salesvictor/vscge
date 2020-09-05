#include "vscge/graphics/vertex_buffer.h"

#include <gl/gl3w.h>

#include <vector>

#include "vscge/graphics/vertex.h"
#include "vscge/util/macro.h"

namespace vs {
Ref<VertexBuffer> VertexBuffer::Make(const std::vector<float>& vertices) {
  return MakeRef<VertexBuffer>(vertices);
}
Ref<VertexBuffer> VertexBuffer::Make(const std::vector<float>& vertices,
                                     const VertexLayout& layout) {
  return MakeRef<VertexBuffer>(vertices, layout);
}

VertexBuffer::VertexBuffer(const std::vector<float>& vertices) {
  glGenBuffers(1, &id_);
  Bind();
  glBufferData(GL_ARRAY_BUFFER,
               vertices.size() * sizeof(VS_VALUE_TYPE(vertices)),
               vertices.data(), GL_STATIC_DRAW);
}
VertexBuffer::VertexBuffer(const std::vector<float>& vertices,
                           const VertexLayout& layout) {
  glGenBuffers(1, &id_);
  Bind();
  glBufferData(GL_ARRAY_BUFFER,
               vertices.size() * sizeof(VS_VALUE_TYPE(vertices)),
               vertices.data(), GL_STATIC_DRAW);
  layout_ = layout;
}

VertexBuffer::~VertexBuffer() { Release(); }
void VertexBuffer::Release() {
  glDeleteBuffers(1, &id_);
  id_ = 0;
}

void VertexBuffer::Bind() const { glBindBuffer(GL_ARRAY_BUFFER, id_); }
void VertexBuffer::Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }
}  // namespace vs
