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

#ifndef VSCGE_INCLUDE_VSCGE_CORE_RENDERER_H_
#define VSCGE_INCLUDE_VSCGE_CORE_RENDERER_H_

#include <Windows.h>

#include <string>
#include <vector>

#include "vscge/api.h"
#include "vscge/core/types.h"
#include "vscge/core/window.h"

namespace vs {
class VS_API Renderer {
 public:
  void Initialize(const Window& window, const Size& pixel_size);

  void ClearScreen();

  // void DrawBuffer(const std::vector<Vertex>& buffer);
  // void DrawLine(const Point& p1, const Point& p2,
  // const VertexProps& props = {});
  // void DrawRect(const Rect& rect, const VertexProps& props = {});
  // void FillRect(const Rect& rect, const VertexProps& props = {});

  void Render();
};
}  // namespace vs

#endif  // VSCGE_INCLUDE_VSCGE_CORE_RENDERER_H_
