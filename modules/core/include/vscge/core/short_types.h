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

#ifndef VSCGE_INCLUDE_VSCGE_CORE_SHORT_TYPES_H_
#define VSCGE_INCLUDE_VSCGE_CORE_SHORT_TYPES_H_

// NOTE(Victor): For some reason, cstdint doesn't have int8_t here...
#include <stdint.h>

// int
using i8  = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

// unsigned int
using uint = unsigned int;
using ui8  = uint8_t;
using ui16 = uint16_t;
using ui32 = uint32_t;
using ui64 = uint64_t;

// float
using f32 = float;
using f64 = double;

#endif  // VSCGE_INCLUDE_VSCGE_CORE_SHORTE_TYPES_H_