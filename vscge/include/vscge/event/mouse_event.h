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

#include <string>

#include "vscge/core/api.h"
#include "vscge/core/types.h"
#include "vscge/event/event.h"

namespace vs {
struct VS_API MouseButtons {
  bool left  = false;
  bool right = false;
};

struct VS_API MouseEvent : public Event {
  MouseEvent() = default;
  MouseEvent(const Point& position, const MouseButtons& buttons)
      : position{position}, buttons{buttons} {}

  virtual ~MouseEvent() = default;

  Point position;
  MouseButtons buttons;

  static constexpr EventType TypeStatic() { return EventType::kMouse; }
  std::string TypeName() const override { return "MouseEvent"; }
  EventType Type() const override { return EventType::kMouse; }
};

struct VS_API MouseMovedEvent final : public MouseEvent {
  MouseMovedEvent(Point before, Point after, MouseButtons buttons)
      : MouseEvent(after, buttons), movement{after - before} {}

  Point movement;

  static constexpr EventType TypeStatic() { return EventType::kMouseMoved; }
  std::string TypeName() const override { return "MouseMovedEvent"; }
  EventType Type() const override { return EventType::kMouseMoved; }
};

struct VS_API MouseButtonPressedEvent final : public MouseEvent {
  using MouseEvent::MouseEvent;  // Nothing new to add.
  static constexpr EventType TypeStatic() {
    return EventType::kMouseButtonPressed;
  }
  std::string TypeName() const override { return "MouseButtonPressedEvent"; }
  EventType Type() const override { return EventType::kMouseButtonPressed; }
};

struct VS_API MouseButtonReleasedEvent final : public MouseEvent {
  using MouseEvent::MouseEvent;  // Nothing new to add.
  static constexpr EventType TypeStatic() {
    return EventType::kMouseButtonReleased;
  }
  std::string TypeName() const override { return "MouseButtonReleasedEvent"; }
  EventType Type() const override { return EventType::kMouseButtonReleased; }
};
}  // namespace vs

#endif  // VSCGE_INCLUDE_VSCGE_EVENT_MOUSE_EVENT_H_
