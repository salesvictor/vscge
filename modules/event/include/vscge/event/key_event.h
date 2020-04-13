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

#ifndef VSCGE_INCLUDE_VSCGE_EVENT_KEY_EVENT_H_
#define VSCGE_INCLUDE_VSCGE_EVENT_KEY_EVENT_H_

#include <Windows.h>

#include <string>

#include "vscge/api.h"
#include "vscge/event/base_event.h"

namespace vs {
enum class Key {
  // Arrow keys
  kLeft,
  kUp,
  kRight,
  kDown,

  kBack,
  kTab,
  kReturn,
  kEscape,

  // Modifier keys.
  kShift,
  kControl,
  kAlt,

  // I don't really know.
  kClear,
  kPause,

  kSpace,
  kEnd,
  kHome,
  kSelect,
  kPrint,
  kExecute,
  kInsert,
  kDelete,

  // Alphanumeric keys.
  k0,
  k1,
  k2,
  k3,
  k4,
  k5,
  k6,
  k7,
  k8,
  k9,

  kA,
  kB,
  kC,
  kD,
  kE,
  kF,
  kG,
  kH,
  kI,
  kJ,
  kK,
  kL,
  kM,
  kN,
  kO,
  kP,
  kQ,
  kR,
  kS,
  kT,
  kU,
  kV,
  kW,
  kX,
  kY,
  kZ,

  kNumpad0,
  kNumpad1,
  kNumpad2,
  kNumpad3,
  kNumpad4,
  kNumpad5,
  kNumpad6,
  kNumpad7,
  kNumpad8,
  kNumpad9,

  // Keypad operations.
  kMultiply,
  kAdd,
  kSeparator,
  kSubtract,
  kDecimal,
  kDivide,

  // Function keys.
  kF1,
  kF2,
  kF3,
  kF4,
  kF5,
  kF6,
  kF7,
  kF8,
  kF9,
  kF10,
  kF11,
  kF12,

  kNumlock,
  kScroll,
};

struct VS_API KeyEvent : public Event {
  KeyEvent() = default;
  explicit KeyEvent(Key key) : key(key) {}

  virtual ~KeyEvent() = default;

  Key key;

  static constexpr EventType TypeStatic() { return EventType::kKey; }
  std::string TypeName() const override { return "KeyEvent"; }
  EventType Type() const override { return EventType::kKey; }
};

struct VS_API KeyPressedEvent final : public KeyEvent {
  using KeyEvent::KeyEvent;  // Nothing new to add.
  static constexpr EventType TypeStatic() { return EventType::kKeyPressed; }
  std::string TypeName() const override { return "KeyPressedEvent"; }
  EventType Type() const override { return EventType::kKeyPressed; }
};

struct VS_API KeyReleasedEvent final : public KeyEvent {
  using KeyEvent::KeyEvent;  // Nothing new to add.
  static constexpr EventType TypeStatic() { return EventType::kKeyReleased; }
  std::string TypeName() const override { return "KeyReleasedEvent"; }
  EventType Type() const override { return EventType::kKeyReleased; }
};
}  // namespace vs

#endif  // VSCGE_INCLUDE_VSCGE_EVENT_KEY_EVENT_H_
