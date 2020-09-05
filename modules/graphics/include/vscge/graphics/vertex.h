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

#ifndef VSCGE_INCLUDE_VSCGE_GRAPHICS_VERTEX_H_
#define VSCGE_INCLUDE_VSCGE_GRAPHICS_VERTEX_H_

#include <initializer_list>
#include <vector>

#include "vscge/api.h"
#include "vscge/debug/debug.h"
#include "vscge/graphics/data_type.h"
#include "vscge/math/vector.h"

namespace vs {
struct VS_API VertexAttrib {
  DataType type;
  std::string_view name;
  bool should_normalize{false};

  const std::size_t ByteSize() const { return DataTypeByteSize(type); }
};

class VS_API VertexLayout {
 public:
  VertexLayout() = default;
  VertexLayout(const std::vector<VertexAttrib>& attribs) : attribs_{attribs} {
    for (const auto& attrib : attribs) {
      size_ += attrib.ByteSize();
    }
  }
  VertexLayout(const std::initializer_list<VertexAttrib>& attribs)
      : attribs_{attribs} {
    for (const auto& attrib : attribs) {
      size_ += attrib.ByteSize();
    }
  }

  std::vector<VertexAttrib>& attribs() { return attribs_; }
  const std::vector<VertexAttrib>& attribs() const { return attribs_; }

  const std::size_t ByteSize() const { return size_; }

  // Iterators boiler-plate
  using iter  = std::vector<VertexAttrib>::iterator;
  using citer = std::vector<VertexAttrib>::const_iterator;

  iter begin() { return attribs_.begin(); }
  iter end() { return attribs_.end(); }
  citer begin() const { return attribs_.begin(); }
  citer end() const { return attribs_.end(); }

 private:
  std::vector<VertexAttrib> attribs_;
  std::size_t size_{0};
};
}  // namespace vs

#endif  // VSCGE_INCLUDE_VSCGE_GRAPHICS_VERTEX_H_
