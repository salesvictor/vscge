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

#include "vscge/core/timer.h"

namespace vs {
float Timestep::Seconds() { return duration.count(); }
float Timestep::Milliseconds() {
  return duration.count() * 1000.0f;  // NOLINT: duration is clearly in seconds.
}

void Stopwatch::Start() { start_time_ = std::chrono::steady_clock::now(); }

Timestep Stopwatch::Stop() {
  end_time_ = std::chrono::steady_clock::now();
  return {end_time_ - start_time_};
}
}  // namespace vs
