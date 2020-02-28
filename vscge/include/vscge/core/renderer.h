#ifndef VSCGE_INCLUDE_VSCGE_CORE_RENDERER_H
#define VSCGE_INCLUDE_VSCGE_CORE_RENDERER_H

#include <Windows.h>

#include <string>
#include <vector>

#include "vscge/core/types.h"
#include "vscge/utils/conversions.h"

namespace vs {
namespace Renderer {
void Initialize(const HANDLE &handle, const Size &window_size,
                const Size &font_size);

const std::vector<Pixel> &GetBuffer();
const Pixel &GetPixelAt(Point location);
const Rect GetWindowRect();

void DrawPixel(const Pixel &pixel);
void DrawBuffer(const std::vector<Pixel> &buffer);
void DrawLine(const Point &p1, const Point &p2);
void DrawRect(const Rect &rect);

void Render();
}  // namespace Renderer
}  // namespace vs

#endif  // VSCGE_INCLUDE_VSCGE_CORE_RENDERER_H