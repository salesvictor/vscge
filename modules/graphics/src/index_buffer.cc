#include "vscge/graphics/index_buffer.h"

#include <gl/gl3w.h>

#include <type_traits>
#include <vector>

#include "vscge/core/short_types.h"
#include "vscge/graphics/vertex.h"
#include "vscge/memory/reference.h"
#include "vscge/util/macro.h"

namespace vs {
Ref<IndexBuffer> IndexBuffer::Make(const std::vector<uint>& indices) {
  return MakeRef<IndexBuffer>(indices);
}

IndexBuffer::IndexBuffer(const std::vector<uint>& indices) {
  glGenBuffers(1, &id_);
  Bind();
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               indices.size() * sizeof(VS_VALUE_TYPE(indices)), indices.data(),
               GL_STATIC_DRAW);
}
IndexBuffer::~IndexBuffer() { Release(); }

void IndexBuffer::Release() {
  glDeleteBuffers(1, &id_);
  id_ = 0;
}

void IndexBuffer::Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_); }
void IndexBuffer::Unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

}  // namespace vs
