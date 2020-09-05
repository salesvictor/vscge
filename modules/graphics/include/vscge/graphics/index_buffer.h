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

#ifndef VSCGE_INCLUDE_VSCGE_GRAPHICS_INDEX_BUFFER_H_
#define VSCGE_INCLUDE_VSCGE_GRAPHICS_INDEX_BUFFER_H_

#include <vector>

#include "vscge/core/short_types.h"
#include "vscge/graphics/detail/class_helper.h"
#include "vscge/graphics/vertex.h"
#include "vscge/memory/reference.h"

namespace vs {
class IndexBuffer {
 public:
  // Use these to create your Buffers! Otherwise you might end up with dangling
  // references!
  static Ref<IndexBuffer> Make(const std::vector<uint>& indices);

  IndexBuffer() = default;
  IndexBuffer(const std::vector<uint>& indices);
  ~IndexBuffer();

  // Move-only class, because copying is "expensive" and "essentialy
  // impossible", see
  // https://www.khronos.org/opengl/wiki/Common_Mistakes#The_Object_Oriented_Language_Problem
  VS_MOVE_ID_ONLY(IndexBuffer);

  void Bind() const;
  void Unbind() const;

 private:
  uint id_{0};  // Zero means invalid

  void Release();
};
}  // namespace vs

#endif  // VSCGE_INCLUDE_VSCGE_GRAPHICS_INDEX_BUFFER_H_
