#ifndef VSCGE_INCLUDE_VSCGE_EVENT_KEY_EVENT_H
#define VSCGE_INCLUDE_VSCGE_EVENT_KEY_EVENT_H

#include "vscge/core/core.h"
#include "vscge/event/event.h"

namespace vs {
struct VS_API KeyEvent : public Event {
  KeyEvent(bool is_down, int key) : is_down(is_down), key(key){};
  bool is_down;
  int key;

  virtual EventType Type() const override { return EventType::KeyPressed; }
};
}  // namespace vs

#endif  // VSCGE_INCLUDE_VSCGE_EVENT_KEY_EVENT_H