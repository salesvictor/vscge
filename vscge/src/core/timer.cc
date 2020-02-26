#include "vscge/core/timer.h"

namespace vs {
float Timestep::GetSeconds() {
  return duration.count();
}

float Timestep::GetMilliseconds() {
  return duration.count() * 1000.f;
}

void Timer::Start() {
    start_time_ = std::chrono::steady_clock::now();
}

Timestep Timer::Stop() {
    end_time_ = std::chrono::steady_clock::now();
    return {end_time_ - start_time_};
}
}