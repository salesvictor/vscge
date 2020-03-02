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

#ifndef VSCGE_INCLUDE_VSCGE_EVENT_MOUSE_EVENT_H_
#define VSCGE_INCLUDE_VSCGE_EVENT_MOUSE_EVENT_H_

#include "vscge/event/event.h"

namespace vs {
enum class MouseButton {
  kLeft = FROM_LEFT_1ST_BUTTON_PRESSED,
  kRight = RIGHTMOST_BUTTON_PRESSED,
};

struct MouseEvent : public Event {
  MouseEvent(int x, int y, MouseButton button) : x{x}, y{y}, button{button} {}

  int x;
  int y;
  MouseButton button;

  static constexpr EventType TypeStatic() { return EventType::kMouseClick; }
  EventType Type() const override { return EventType::kMouseClick; }
};
}  // namespace vs

#endif  // VSCGE_INCLUDE_VSCGE_EVENT_MOUSE_EVENT_H_
