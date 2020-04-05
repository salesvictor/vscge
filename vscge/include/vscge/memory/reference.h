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

#ifndef VSCGE_INCLUDE_VSCGE_MEMORY_REFERENCE_H_
#define VSCGE_INCLUDE_VSCGE_MEMORY_REFERENCE_H_

#include <memory>

namespace vs {
template <typename Type>
using Ref = std::shared_ptr<Type>;

template <typename Type, typename... Args>
constexpr Ref<Type> CreateRef(Args&&... args) {
  return std::make_shared<Type>(std::forward<Args>(args)...);
}
}  // namespace vs

#endif  // VSCGE_INCLUDE_VSCGE_MEMORY_REFERENCE_H_
