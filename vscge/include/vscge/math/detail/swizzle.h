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

#ifndef VSCGE_INCLUDE_VSCGE_MATH_DETAIL_SWIZZLE_H_
#define VSCGE_INCLUDE_VSCGE_MATH_DETAIL_SWIZZLE_H_

#include "vscge/core/api.h"

// TODO(Victor): Disabling these for now, check if really should
#pragma warning(disable : 4717 4789)

// Adapted from
// https://stackoverflow.com/questions/41698446/c-variadic-vector-operator-implementation

namespace vs {
namespace detail {
template <template <typename> class VecT1, class Elem1, int... idxs1>
struct VS_LOCAL Swizzle;

template <class Elem>
struct VS_LOCAL Vec1Base {
  std::array<Elem, 1> data;

  operator Elem() const { return data[0]; }

  template <int index>
  Vec1Base(const Swizzle<Vec1Base, Elem, index>& swizzle) {
    data[0] = swizzle[index];
  }
};

template <template <typename> class VecT1, class Elem1, int... idxs1>
struct VS_LOCAL Swizzle {
  Elem1& operator[](int index) { return reinterpret_cast<Elem1*>(this)[index]; }
  const Elem1& operator[](int index) const {
    return reinterpret_cast<const Elem1*>(this)[index];
  }

  // Formatting off to let the preprocessor work
  // clang-format off
#define CREATE_ARITHMETIC_OPERATOR(op)                                       \
  template <template <typename> class VecT2, class Elem2, int... idxs2>      \
  Swizzle& operator op##=(const Swizzle<VecT2, Elem2, idxs2...>& other) {    \
    static_assert(sizeof...(idxs1) == sizeof...(idxs2),                      \
                  "Your swizzles have different sizes!");                    \
                                                                             \
    (((*this)[idxs1] op##= other[idxs2]), ...);                              \
    return *this;                                                            \
  }                                                                          \
  template <template <typename> class VecT2, class Elem2, int... idxs2>      \
  friend Swizzle operator op(Swizzle left,                                   \
                             const Swizzle<VecT2, Elem2, idxs2...>& right) { \
    static_assert(sizeof...(idxs1) == sizeof...(idxs2),                      \
                  "Your swizzles have different sizes!");                    \
                                                                             \
    left op##= right;                                                        \
    return left;                                                             \
  }                                                                          \
  Swizzle& operator op##=(const Elem1& elem) {                               \
    (((*this)[idxs1] op##= elem), ...);                                      \
    return *this;                                                            \
  }                                                                          \
  friend Swizzle operator op(const Elem1& elem, Swizzle swizzle) {           \
    ((swizzle[idxs1] = swizzle[idxs1] op elem), ...);                        \
    return swizzle;                                                          \
  }
  // clang-format on

  CREATE_ARITHMETIC_OPERATOR(+);
  CREATE_ARITHMETIC_OPERATOR(-);
  CREATE_ARITHMETIC_OPERATOR(*);
  CREATE_ARITHMETIC_OPERATOR(/);

#define CREATE_RELATIONAL_OPERATOR(op)                                   \
  template <template <typename> class VecT2, class Elem2, int... idxs2>  \
  bool operator op(const Swizzle<VecT2, Elem2, idxs2...>& other) const { \
    static_assert(sizeof...(idxs1) == sizeof...(idxs2),                  \
                  "Your swizzles have different sizes!");                \
                                                                         \
    return (((*this)[idxs1] op other[idxs2]) && ...);                    \
  }                                                                      \
  bool operator op(const Elem1& elem) const {                            \
    return (((*this)[idxs1] op elem) && ...);                            \
  }
  // friend bool operator op(const Elem1& elem, const Swizzle& swizzle) {   \
    // return ((elem op swizzle[idxs1]) && ...);                            \
  // }

  CREATE_RELATIONAL_OPERATOR(==);
  CREATE_RELATIONAL_OPERATOR(<=);
  CREATE_RELATIONAL_OPERATOR(<);
  CREATE_RELATIONAL_OPERATOR(>=);
  CREATE_RELATIONAL_OPERATOR(>);
};

// TODO(Victor): MSVC is broken as of 19.25, it will be fixed with Visual
// Studio 16.7.
template <template <typename> class VecT1, class Elem1, int... idxs1>
bool operator==(const Elem1& elem,
                const Swizzle<VecT1, Elem1, idxs1...>& swizzle) {
  return ((elem == swizzle[idxs1]) && ...);
}
template <template <typename> class VecT1, class Elem1, int... idxs1>
bool operator<=(const Elem1& elem,
                const Swizzle<VecT1, Elem1, idxs1...>& swizzle) {
  return ((elem <= swizzle[idxs1]) && ...);
}
template <template <typename> class VecT1, class Elem1, int... idxs1>
bool operator<(const Elem1& elem,
               const Swizzle<VecT1, Elem1, idxs1...>& swizzle) {
  return ((elem < swizzle[idxs1]) && ...);
}
template <template <typename> class VecT1, class Elem1, int... idxs1>
bool operator>=(const Elem1& elem,
                const Swizzle<VecT1, Elem1, idxs1...>& swizzle) {
  return ((elem >= swizzle[idxs1]) && ...);
}
template <template <typename> class VecT1, class Elem1, int... idxs1>
bool operator>(const Elem1& elem,
               const Swizzle<VecT1, Elem1, idxs1...>& swizzle) {
  return ((elem > swizzle[idxs1]) && ...);
}
}  // namespace detail
}  // namespace vs

#endif  // VSCGE_INCLUDE_VSCGE_MATH_DETAIL_SWIZZLE_H_