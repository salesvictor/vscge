#ifndef VSCGE_INCLUDE_VSCGE_CORE_TIMER_H
#define VSCGE_INCLUDE_VSCGE_CORE_TIMER_H

#include <chrono>
#include <ratio>

#include "vscge/core/core.h"


namespace vs {
struct Timestep {
  std::chrono::duration<float> duration;

  VS_API float GetSeconds();
  VS_API float GetMilliseconds();

  operator float() const { return duration.count(); };
};

class Timer {
 public:
  VS_API void Start();
  VS_API Timestep Stop();

 private:
  std::chrono::time_point<std::chrono::steady_clock> start_time_;
  std::chrono::time_point<std::chrono::steady_clock> end_time_;
};
}  // namespace vs

#endif  // VSCGE_INCLUDE_VSCGE_CORE_TIMER_H