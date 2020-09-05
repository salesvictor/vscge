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

#ifndef VSCGE_INCLUDE_VSCGE_GRAPHICS_DATA_TYPE_H_
#define VSCGE_INCLUDE_VSCGE_GRAPHICS_DATA_TYPE_H_

#include <cstddef>

#include "vscge/api.h"

namespace vs {
enum class VS_API DataType {
  kFloat,
  kFloat2,
  kFloat3,
  kFloat4,

  kVec2 = kFloat2,
  kVec3 = kFloat3,
  kVec4 = kFloat4,

  kInt,
  kInt2,
  kInt3,
  kInt4,

  kIVec2 = kInt2,
  kIVec3 = kInt3,
  kIVec4 = kInt4,

  kBool,
  kBool2,
  kBool3,
  kBool4,

  kBVec2 = kBool2,
  kBVec3 = kBool3,
  kBVec4 = kBool4,

  kNull,
};

constexpr std::size_t VS_API DataTypeElemCount(DataType type) {
  switch (type) {
    case DataType::kBool:
    case DataType::kInt:
    case DataType::kFloat:
      return 1;

    case DataType::kBool2:
    case DataType::kInt2:
    case DataType::kFloat2:
      return 2;

    case DataType::kBool3:
    case DataType::kInt3:
    case DataType::kFloat3:
      return 3;

    case DataType::kBool4:
    case DataType::kInt4:
    case DataType::kFloat4:
      return 4;

    default: {
      VS_ASSERT(false);
      return 0;
    }
  }
}

constexpr std::size_t VS_API DataTypeByteSize(DataType type) {
  switch (type) {
    case DataType::kInt:
    case DataType::kFloat:
    case DataType::kInt2:
    case DataType::kFloat2:
    case DataType::kInt3:
    case DataType::kFloat3:
    case DataType::kInt4:
    case DataType::kFloat4:
      return 4 * DataTypeElemCount(type);

    case DataType::kBool:
    case DataType::kBool2:
    case DataType::kBool3:
    case DataType::kBool4:
      return 1 * DataTypeElemCount(type);

    default: {
      VS_ASSERT(false);
      return 0;
    }
  }
}
}  // namespace vs

#endif  // VSCGE_INCLUDE_VSCGE_GRAPHICS_DATA_TYPE_H_
