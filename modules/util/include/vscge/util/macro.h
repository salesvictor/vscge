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

#ifndef VSCGE_INCLUDE_VSCGE_UTILS_MACRO_H_
#define VSCGE_INCLUDE_VSCGE_UTILS_MACRO_H_

#include <type_traits>

#define VS_BIND_EVENT(fn)  [this](auto ev) { fn(ev); }
#define VS_BIND_THREAD(fn) [this]() { fn(); }

#define VS_STR(str)      VS_STR_IMPL(str)
#define VS_STR_IMPL(str) #str

#define VS_VALUE_TYPE(var) std::decay_t<decltype((var))>::value_type

#endif  // VSCGE_INCLUDE_VSCGE_UTILS_MACRO_H_
