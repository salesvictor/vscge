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

#ifndef VSCGE_INCLUDE_VSCGE_GRAPHICS_VERTEX_ARRAY_H_
#define VSCGE_INCLUDE_VSCGE_GRAPHICS_VERTEX_ARRAY_H_

#include <vector>

#include "vscge/core/short_types.h"
#include "vscge/graphics/index_buffer.h"
#include "vscge/graphics/vertex.h"
#include "vscge/graphics/vertex_buffer.h"
#include "vscge/memory/reference.h"

namespace vs {
class VertexArray {
 public:
  VertexArray();
  ~VertexArray();

  void Bind() const;
  void Unbind() const;

  void AddVertexBuffer(const Ref<VertexBuffer>&);
  void SetIndexBuffer(const Ref<IndexBuffer>&);

 private:
  uint id_;

  // These need to be `Ref` to prevent creation of other ids!
  std::vector<Ref<VertexBuffer>> vertex_buffers_;
  Ref<IndexBuffer> index_buffer_;
};
}  // namespace vs

#endif  // VSCGE_INCLUDE_VSCGE_GRAPHICS_VERTEX_ARRAY_H_
