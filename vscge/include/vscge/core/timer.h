#ifndef VSCGE_INCLUDE_VSCGE_CORE_TIMER_H_
#define VSCGE_INCLUDE_VSCGE_CORE_TIMER_H_

#include <chrono>
#include <ratio>

#include "vscge/core/core.h"

namespace vs {
struct VS_API Timestep {
  std::chrono::duration<float> duration;

  float GetSeconds();
  float GetMilliseconds();

  operator float() const { return duration.count(); }
};

class VS_API Timer {
 public:
  void Start();
  Timestep Stop();

 private:
  std::chrono::time_point<std::chrono::steady_clock> start_time_;
  std::chrono::time_point<std::chrono::steady_clock> end_time_;
};
}  // namespace vs

#endif  // VSCGE_INCLUDE_VSCGE_CORE_TIMER_H_
