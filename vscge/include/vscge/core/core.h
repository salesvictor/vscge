// Copyright 2020 Victor Sales

#ifndef VSCGE_INCLUDE_VSCGE_CORE_CORE_H_
#define VSCGE_INCLUDE_VSCGE_CORE_CORE_H_

#ifdef _WIN32
#  pragma warning(disable : 4251)
#  ifdef vscge_EXPORTS
#    define VS_API __declspec(dllexport)
#  else
#    define VS_API __declspec(dllimport)
#  endif  // vscge_EXPORTS
#else
#  define VS_API
#endif  // _WIN32

#include <functional>
#include <memory>
#include <utility>

#define VS_BIND_EVENT(fn) [this](auto ev) { fn(ev); }
#define VS_BIND_THREAD(fn) [this]() { fn(); }

namespace vs {
template <class Type>
using Ref = std::shared_ptr<Type>;

template <class Type, typename... Args>
constexpr Ref<Type> CreateRef(Args&&... args) {
  return std::make_shared<Type>(std::forward<Args>(args)...);
}
}  // namespace vs

#endif  // VSCGE_INCLUDE_VSCGE_CORE_CORE_H_
