#ifndef VSCGE_INCLUDE_VSCGE_UTILS_PIXEL_CONVERTER_H
#define VSCGE_INCLUDE_VSCGE_UTILS_PIXEL_CONVERTER_H

#include <string_view>
#include <vector>

#include "vscge/core/types.h"

namespace vs {
VS_API Point BufferIndexToPoint(const Rect &region, int i);
VS_API int PointToBufferIndex(const Rect &region, const Point &point);

VS_API std::vector<Pixel> StringToPixelBuffer(std::wstring_view string_buffer,
                                       const Rect &region);
}  // namespace vs

#endif  // VSCGE_INCLUDE_VSCGE_UTILS_PIXEL_CONVERTER_H