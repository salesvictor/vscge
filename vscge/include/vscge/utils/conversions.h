#ifndef VSCGE_INCLUDE_UTILS_PIXEL_CONVERTER_H
#define VSCGE_INCLUDE_UTILS_PIXEL_CONVERTER_H

#include "vscge/core/types.h"

#include <string>
#include <vector>

namespace vs {
Point BufferIndexToPoint(const Rect &region, int i);
int PointToBufferIndex(const Rect &region, const Point &point);

std::vector<Pixel> StringToPixelBuffer(std::wstring_view string_buffer, const Rect &region);
}

#endif // VSCGE_INCLUDE_UTILS_PIXEL_CONVERTER_H