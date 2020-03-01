#ifndef VSCGE_INCLUDE_VSCGE_EVENT_EVENT_H_
#define VSCGE_INCLUDE_VSCGE_EVENT_EVENT_H_

#include "vscge/core/core.h"

namespace vs {
enum class EventType {
  kKeyPressed,
  kMouseClick,
};

struct VS_API Event {
  virtual EventType Type() const = 0;
};

class VS_API EventDispatcher {
 public:
  explicit EventDispatcher(Ref<Event> event) : event_{event} {}

  template <typename Type, typename Fn>
  void Dispatch(const Fn& fn) {
    if (event_->Type() == Type::TypeStatic())
      fn(std::static_pointer_cast<Type>(event_));
  }

 private:
  Ref<Event> event_;
};
}  // namespace vs

#endif  // VSCGE_INCLUDE_VSCGE_EVENT_EVENT_H_
