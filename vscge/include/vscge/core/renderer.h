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

#include "vscge/core/api.h"
#include "vscge/core/types.h"

/*
namespace vs {
// TODO(Victor): See if it makes sense for Renderer to be a static class, if
// not, change the namespace to be lower case.
namespace Renderer {
void VS_API Initialize(const HANDLE& handle, const Size& window_size,
                       const Size& font_size);

const VS_API std::vector<PixelProps>& GetBuffer();
const VS_API PixelProps& GetPixelPropsAt(Point location);
const VS_API Rect GetWindowRect();

void VS_API ClearScreen();

void VS_API DrawPixel(const Pixel& pixel);
void VS_API DrawBuffer(const std::vector<Pixel>& buffer);
void VS_API DrawLine(const Point& p1, const Point& p2,
                     const PixelProps& props = {});
void VS_API DrawRect(const Rect& rect, const PixelProps& props = {});
void VS_API FillRect(const Rect& rect, const PixelProps& props = {});

void VS_API Render();
}  // namespace Renderer
}  // namespace vs
*/

#endif  // VSCGE_INCLUDE_VSCGE_CORE_RENDERER_H_
