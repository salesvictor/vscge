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

#ifndef VSCGE_INCLUDE_VSCGE_DEBUG_DEBUG_H_
#define VSCGE_INCLUDE_VSCGE_DEBUG_DEBUG_H_

#include <string>

#include "vscge/core/api.h"

#if defined(_MSC_VER)
#  define VS_FUNC_LOG __FUNCSIG__
#elif defined(__GNUC__)
#  define VS_FUNC_LOG __PRETTY_FUNC__
#else
#  error "Unknown compiler"
#endif

// TODO(Victor): For some reason this macro adds a lot of overhead to the calls
// everywhere...
#ifdef VS_ENABLE_ASSERTS
#  define VS_ASSERT(cond)                                                  \
    (!!(cond) || ::vs::debug::Fail(VS_STR(cond), (const char*)VS_FUNC_LOG, \
                                   VS_STR(__LINE__), __FILE__))
#else
#  define VS_ASSERT(cond)
#endif

namespace vs {
namespace debug {
[[noreturn]] VS_API void Fail(std::string cond, std::string function,
                              std::string line, std::string file);
}  // namespace debug
}  // namespace vs

#endif  // VSCGE_INCLUDE_VSCGE_DEBUG_DEBUG_H_
