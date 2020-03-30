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

#ifndef VSCGE_INCLUDE_VSCGE_EVENT_BASE_EVENT_H_
#define VSCGE_INCLUDE_VSCGE_EVENT_BASE_EVENT_H_

#include <string>

#include "vscge/core/api.h"
#include "vscge/memory/memory.h"

namespace vs {
// TODO(Victor): These events are not mutually exclusive, maybe represent them
// as a bitfield?
enum class EventType {
  kKey,  // Generic key event, for when you don't care.
  kKeyPressed,
  kKeyReleased,
  kMouse,  // Generic mouse event, for when you don't care.
  kMouseMoved,
  kMouseButtonPressed,
  kMouseButtonReleased,
};

// TODO(Victor): See if it makes sense to add a `handled` to Event.
struct VS_API Event {
  virtual ~Event()                     = default;
  virtual EventType Type() const       = 0;
  virtual std::string TypeName() const = 0;
};

class VS_API EventDispatcher {
 public:
  explicit EventDispatcher(Ref<Event> event) : event_{event} {}

  // TODO(Victor): I really do not like having a `TypeStatic()` function, but
  // the only other way I found was a `dynamic_cast`, maybe there's a better way
  // with C++ specific idioms.
  template <typename Type, typename Fn>
  void Dispatch(const Fn& fn) {
    if (event_->Type() == Type::TypeStatic())
      fn(std::static_pointer_cast<Type>(event_));
  }

 private:
  Ref<Event> event_;
};
}  // namespace vs

#endif  // VSCGE_INCLUDE_VSCGE_EVENT_BASE_EVENT_H_
