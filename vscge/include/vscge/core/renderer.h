// Copyright 2020 Victor Sales

#ifndef VSCGE_INCLUDE_VSCGE_CORE_RENDERER_H_
#define VSCGE_INCLUDE_VSCGE_CORE_RENDERER_H_

#include <Windows.h>

#include <string>
#include <vector>

#include "vscge/core/core.h"
#include "vscge/core/types.h"
#include "vscge/utils/conversions.h"

namespace vs {
namespace Renderer {
void VS_API Initialize(const HANDLE &handle, const Size &window_size,
                       const Size &font_size);

const VS_API std::vector<Pixel> &GetBuffer();
const VS_API Pixel &GetPixelAt(Point location);
const VS_API Rect GetWindowRect();

void VS_API ClearScreen();

void VS_API DrawPixel(const Pixel &pixel);
void VS_API DrawBuffer(const std::vector<Pixel> &buffer);
void VS_API DrawLine(const Point &p1, const Point &p2,
                     const PixelProps &props = {});
void VS_API DrawRect(const Rect &rect, const PixelProps &props = {});
void VS_API FillRect(const Rect &rect, const PixelProps &props = {});

void VS_API Render();
}  // namespace Renderer
}  // namespace vs

#endif  // VSCGE_INCLUDE_VSCGE_CORE_RENDERER_H_
