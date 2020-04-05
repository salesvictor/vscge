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

#ifndef VSCGE_INCLUDE_VSCGE_CORE_TIMER_H_
#define VSCGE_INCLUDE_VSCGE_CORE_TIMER_H_

#include <chrono>
#include <ratio>

#include "vscge/api.h"

namespace vs {
struct VS_API Timestep {
  std::chrono::duration<float> duration;

  float Seconds();
  float Milliseconds();

  operator float() const { return duration.count(); }
};

class VS_API Stopwatch {
 public:
  void Start();
  Timestep Stop();

 private:
  std::chrono::time_point<std::chrono::steady_clock> start_time_;
  std::chrono::time_point<std::chrono::steady_clock> end_time_;
};
}  // namespace vs

#endif  // VSCGE_INCLUDE_VSCGE_CORE_TIMER_H_
