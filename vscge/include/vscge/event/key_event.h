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

#include "vscge/core/core.h"
#include "vscge/event/event.h"

namespace vs {
enum class Key {
  kEscape = VK_ESCAPE,

  kLeft = VK_LEFT,
  kUp = VK_UP,
  kRight = VK_RIGHT,
  kDown = VK_DOWN,

  kBack = VK_BACK,
  kTab = VK_TAB,

  kReturn = VK_RETURN,
  kShift = VK_SHIFT,
  kControl = VK_CONTROL,

  kClear = VK_CLEAR,
  kMenu = VK_MENU,
  kPause = VK_PAUSE,

  kSpace = VK_SPACE,
  kEnd = VK_END,
  kHome = VK_HOME,
  kSelect = VK_SELECT,
  kPrint = VK_PRINT,
  kExecute = VK_EXECUTE,
  kInsert = VK_INSERT,
  kDelete = VK_DELETE,

  k0 = 0x30,
  k1 = 0x31,
  k2 = 0x32,
  k3 = 0x33,
  k4 = 0x34,
  k5 = 0x35,
  k6 = 0x36,
  k7 = 0x37,
  k8 = 0x38,
  k9 = 0x39,

  kA = 0x41,
  kB = 0x42,
  kC = 0x43,
  kD = 0x44,
  kE = 0x45,
  kF = 0x46,
  kG = 0x47,
  kH = 0x48,
  kI = 0x49,
  kJ = 0x4A,
  kK = 0x4B,
  kL = 0x4C,
  kM = 0x4D,
  kN = 0x4E,
  kO = 0x4F,
  kP = 0x50,
  kQ = 0x51,
  kR = 0x52,
  kS = 0x53,
  kT = 0x54,
  kU = 0x55,
  kV = 0x56,
  kW = 0x57,
  kX = 0x58,
  kY = 0x59,
  kZ = 0x5A,

  kNumpad0 = VK_NUMPAD0,
  kNumpad1 = VK_NUMPAD1,
  kNumpad2 = VK_NUMPAD2,
  kNumpad3 = VK_NUMPAD3,
  kNumpad4 = VK_NUMPAD4,
  kNumpad5 = VK_NUMPAD5,
  kNumpad6 = VK_NUMPAD6,
  kNumpad7 = VK_NUMPAD7,
  kNumpad8 = VK_NUMPAD8,
  kNumpad9 = VK_NUMPAD9,
  kMultiply = VK_MULTIPLY,
  kAdd = VK_ADD,
  kSeparator = VK_SEPARATOR,
  kSubtract = VK_SUBTRACT,
  kDecimal = VK_DECIMAL,
  kDivide = VK_DIVIDE,

  kF1 = VK_F1,
  kF2 = VK_F2,
  kF3 = VK_F3,
  kF4 = VK_F4,
  kF5 = VK_F5,
  kF6 = VK_F6,
  kF7 = VK_F7,
  kF8 = VK_F8,
  kF9 = VK_F9,
  kF10 = VK_F10,
  kF11 = VK_F11,
  kF12 = VK_F12,

  kNumlock = VK_NUMLOCK,
  kScroll = VK_SCROLL,
};

struct VS_API KeyEvent : public Event {
  KeyEvent(bool is_down, Key key) : is_down(is_down), key(key) {}

  bool is_down;
  Key key;

  static constexpr EventType TypeStatic() { return EventType::kKeyPressed; }
  EventType Type() const override { return EventType::kKeyPressed; }
};
}  // namespace vs

#endif  // VSCGE_INCLUDE_VSCGE_EVENT_KEY_EVENT_H_
