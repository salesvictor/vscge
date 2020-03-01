#ifndef VSCGE_INCLUDE_VSCGE_EVENT_EVENT_H
#define VSCGE_INCLUDE_VSCGE_EVENT_EVENT_H

#include "vscge/core/core.h"

namespace vs {
enum class EventType {
  KeyPressed,
};

struct VS_API Event {
  virtual EventType Type() const = 0;
};
}  // namespace vs

#endif  // VSCGE_INCLUDE_VSCGE_EVENT_EVENT_H