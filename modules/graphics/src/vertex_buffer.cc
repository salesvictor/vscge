#include "vscge/graphics/vertex_buffer.h"

#include <gl/gl3w.h>

#include <vector>

#include "vscge/graphics/vertex.h"

namespace vs {
VertexBuffer::VertexBuffer(const std::vector<Vertex>& vertices) {
  glGenBuffers(1, &id_);
  glBindBuffer(GL_ARRAY_BUFFER, id_);

  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vs::Vertex),
               vertices.data(), GL_STATIC_DRAW);
}
VertexBuffer::~VertexBuffer() { glDeleteBuffers(1, &id_); }

}  // namespace vs
