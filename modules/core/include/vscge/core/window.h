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

#ifndef VSCGE_INCLUDE_VSCGE_CORE_WINDOW_H_
#define VSCGE_INCLUDE_VSCGE_CORE_WINDOW_H_

#include <atomic>
#include <mutex>

#include "vscge/api.h"
#include "vscge/core/types.h"

namespace vs {
namespace platform {
class VS_API Window {
 public:
  Size size_;

  void Initialize();

  // TODO(Victor): Check if these **really** need to be static...
  static inline std::atomic<bool> is_running_ = true;
  static inline std::mutex closing_;
  static inline std::condition_variable has_finished_;

 private:
  void InputHandler();
};
}  // namespace platform
}  // namespace vs

#endif  // VSCGE_INCLUDE_VSCGE_CORE_WINDOW_H_
