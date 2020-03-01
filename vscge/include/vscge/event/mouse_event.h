#ifndef VSCGE_INCLUDE_VSCGE_EVENT_MOUSE_EVENT_H
#define VSCGE_INCLUDE_VSCGE_EVENT_MOUSE_EVENT_H

#include "vscge/event/event.h"

namespace vs {
enum class MouseButton {
  kLeft = FROM_LEFT_1ST_BUTTON_PRESSED,
  kRight = RIGHTMOST_BUTTON_PRESSED,
};

struct MouseEvent : public Event {
  MouseEvent(int x, int y, MouseButton button) : x{x}, y{y}, button{button} {};

  int x;
  int y;
  MouseButton button;

  virtual EventType Type() const override { return EventType::kMouseClick; }
};
}  // namespace vs

#endif  // VSCGE_INCLUDE_VSCGE_EVENT_MOUSE_EVENT_H