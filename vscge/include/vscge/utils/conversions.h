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

#ifndef VSCGE_INCLUDE_VSCGE_UTILS_CONVERSIONS_H_
#define VSCGE_INCLUDE_VSCGE_UTILS_CONVERSIONS_H_

#include <string_view>
#include <unordered_map>
#include <vector>

#include "vscge/core/core.h"
#include "vscge/core/types.h"

namespace vs {
VS_API Point BufferIndexToPoint(const Rect& region, int i);
VS_API int PointToBufferIndex(const Rect& region, const Point& point);

VS_API std::vector<Pixel> StringToPixelBuffer(
    std::string_view string_buffer, const Rect& region,
    std::unordered_map<char, PixelProps> char_map);
}  // namespace vs

#endif  // VSCGE_INCLUDE_VSCGE_UTILS_CONVERSIONS_H_
