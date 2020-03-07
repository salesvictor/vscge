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

#ifndef VSCGE_INCLUDE_VSCGE_CORE_CORE_H_
#define VSCGE_INCLUDE_VSCGE_CORE_CORE_H_

#ifdef _WIN32
#  pragma warning(disable : 4251)
#  ifdef vscge_EXPORTS
#    define VS_API __declspec(dllexport)
#  else
#    define VS_API __declspec(dllimport)
#  endif  // vscge_EXPORTS
#else
#  define VS_API
#endif  // _WIN32

#include <functional>
#include <memory>
#include <utility>

#define VS_BIND_EVENT(fn) [this](auto ev) { fn(ev); }
#define VS_BIND_THREAD(fn) [this]() { fn(); }

#define VS_STR(str) VS_STR_IMPL(str)
#define VS_STR_IMPL(str) #str

namespace vs {
template <class Type>
using Ref = std::shared_ptr<Type>;

template <class Type, typename... Args>
constexpr Ref<Type> CreateRef(Args &&... args) {
  return std::make_shared<Type>(std::forward<Args>(args)...);
}
}  // namespace vs

#endif  // VSCGE_INCLUDE_VSCGE_CORE_CORE_H_
