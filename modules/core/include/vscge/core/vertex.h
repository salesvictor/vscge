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

#ifndef VSCGE_INCLUDE_VSCGE_CORE_VERTEX_H_
#define VSCGE_INCLUDE_VSCGE_CORE_VERTEX_H_

#include "vscge/api.h"
#include "vscge/math/vector.h"

namespace vs {
inline Vec3 kInvalidColor(-1.0f);
inline Vec2 kInvalidUv(-1.0f);

struct VS_API VertexProps {
  Vec3 color{kInvalidColor};
  Vec2 uv{kInvalidUv};  // Texture coords
};

inline VertexProps kInvalidProps{{kInvalidColor}, {kInvalidUv}};

struct VS_API Vertex {
  Vec3 pos{};
  VertexProps props{};
};
}  // namespace vs

#endif  // VSCGE_INCLUDE_VSCGE_CORE_VERTEX_H_