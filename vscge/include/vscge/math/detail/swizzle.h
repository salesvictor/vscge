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
template <template <typename> class VecT1, class Elem1, std::size_t... idxs1>
struct VS_LOCAL Swizzle;

template <class Elem>
struct VS_LOCAL Vec1Base : Swizzle<Vec1Base, Elem, 0> {
  std::array<Elem, 1> data;

  operator Elem() const { return data[0]; }

  template <std::size_t index>
  Vec1Base(const Swizzle<Vec1Base, Elem, index>& swizzle) {
    data[0] = swizzle[index];
  }
};

template <template <typename> class VecT1, class Elem1, std::size_t... idxs1>
struct VS_LOCAL Swizzle {
  Elem1& operator[](std::size_t index) {
    return reinterpret_cast<Elem1*>(this)[index];
  }
  const Elem1& operator[](std::size_t index) const {
    return reinterpret_cast<const Elem1*>(this)[index];
  }

  Swizzle() = default;
  Swizzle(const Swizzle& other) { (((*this)[idxs1] = other[idxs1]), ...); }

  // NOTE(Victor): We need this move constructor because the arithmetic
  // operators uses it!
  Swizzle(Swizzle&& other) { (((*this)[idxs1] = other[idxs1]), ...); }

  // TODO(Victor): Maybe use a python script to generate all the operators and
  // `#include` them here?
  template <template <typename> class VecT2, class Elem2, std::size_t... idxs2>
  Swizzle& operator=(const Swizzle<VecT2, Elem2, idxs2...>& other) {
    static_assert(sizeof...(idxs1) == sizeof...(idxs2),
                  "Your swizzles have different sizes!");

    (((*this)[idxs1] = other[idxs2]), ...);
    return *this;
  }
  Swizzle& operator=(const Elem1& elem) {
    (((*this)[idxs1] += elem), ...);
    return *this;
  }

  template <template <typename> class VecT2, class Elem2, std::size_t... idxs2>
  Swizzle& operator+=(const Swizzle<VecT2, Elem2, idxs2...>& other) {
    static_assert(sizeof...(idxs1) == sizeof...(idxs2),
                  "Your swizzles have different sizes!");

    (((*this)[idxs1] += other[idxs2]), ...);
    return *this;
  }
  template <template <typename> class VecT2, class Elem2, std::size_t... idxs2>
  friend VecT1<Elem1> operator+(Swizzle left,
                                const Swizzle<VecT2, Elem2, idxs2...>& right) {
    static_assert(sizeof...(idxs1) == sizeof...(idxs2),
                  "Your swizzles have different sizes!");

    left += right;
    return left;
  }
  Swizzle& operator+=(const Elem1& elem) {
    (((*this)[idxs1] += elem), ...);
    return *this;
  }
  friend VecT1<Elem1> operator+(const Elem1& elem, Swizzle swizzle) {
    ((swizzle[idxs1] = elem + swizzle[idxs1]), ...);
    return swizzle;
  }

  template <template <typename> class VecT2, class Elem2, std::size_t... idxs2>
  Swizzle& operator-=(const Swizzle<VecT2, Elem2, idxs2...>& other) {
    static_assert(sizeof...(idxs1) == sizeof...(idxs2),
                  "Your swizzles have different sizes!");

    (((*this)[idxs1] -= other[idxs2]), ...);
    return *this;
  }
  template <template <typename> class VecT2, class Elem2, std::size_t... idxs2>
  friend VecT1<Elem1> operator-(Swizzle left,
                                const Swizzle<VecT2, Elem2, idxs2...>& right) {
    static_assert(sizeof...(idxs1) == sizeof...(idxs2),
                  "Your swizzles have different sizes!");

    left -= right;
    return left;
  }
  Swizzle& operator-=(const Elem1& elem) {
    (((*this)[idxs1] -= elem), ...);
    return *this;
  }
  friend VecT1<Elem1> operator-(const Elem1& elem, Swizzle swizzle) {
    ((swizzle[idxs1] = elem - swizzle[idxs1]), ...);
    return swizzle;
  }

  template <template <typename> class VecT2, class Elem2, std::size_t... idxs2>
  friend VecT1<Elem1> operator*(Swizzle left,
                                const Swizzle<VecT2, Elem2, idxs2...>& right) {
    static_assert(sizeof...(idxs1) == sizeof...(idxs2),
                  "Your swizzles have different sizes!");

    left *= right;
    return left;
  }
  Swizzle& operator*=(const Elem1& elem) {
    (((*this)[idxs1] *= elem), ...);
    return *this;
  }
  friend VecT1<Elem1> operator*(const Elem1& elem, Swizzle swizzle) {
    ((swizzle[idxs1] = elem * swizzle[idxs1]), ...);
    return swizzle;
  }

  template <template <typename> class VecT2, class Elem2, std::size_t... idxs2>
  friend VecT1<Elem1> operator/(Swizzle left,
                                const Swizzle<VecT2, Elem2, idxs2...>& right) {
    static_assert(sizeof...(idxs1) == sizeof...(idxs2),
                  "Your swizzles have different sizes!");

    left /= right;
    return left;
  }
  Swizzle& operator/=(const Elem1& elem) {
    (((*this)[idxs1] /= elem), ...);
    return *this;
  }
  friend VecT1<Elem1> operator/(const Elem1& elem, Swizzle swizzle) {
    ((swizzle[idxs1] = elem / swizzle[idxs1]), ...);
    return swizzle;
  }

#define CREATE_RELATIONAL_OPERATOR(op)                                   \
  template <template <typename> class VecT2, class Elem2,                \
            std::size_t... idxs2>                                        \
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
template <template <typename> class VecT1, class Elem1, std::size_t... idxs1>
bool operator==(const Elem1& elem,
                const Swizzle<VecT1, Elem1, idxs1...>& swizzle) {
  return ((elem == swizzle[idxs1]) && ...);
}
template <template <typename> class VecT1, class Elem1, std::size_t... idxs1>
bool operator<=(const Elem1& elem,
                const Swizzle<VecT1, Elem1, idxs1...>& swizzle) {
  return ((elem <= swizzle[idxs1]) && ...);
}
template <template <typename> class VecT1, class Elem1, std::size_t... idxs1>
bool operator<(const Elem1& elem,
               const Swizzle<VecT1, Elem1, idxs1...>& swizzle) {
  return ((elem < swizzle[idxs1]) && ...);
}
template <template <typename> class VecT1, class Elem1, std::size_t... idxs1>
bool operator>=(const Elem1& elem,
                const Swizzle<VecT1, Elem1, idxs1...>& swizzle) {
  return ((elem >= swizzle[idxs1]) && ...);
}
template <template <typename> class VecT1, class Elem1, std::size_t... idxs1>
bool operator>(const Elem1& elem,
               const Swizzle<VecT1, Elem1, idxs1...>& swizzle) {
  return ((elem > swizzle[idxs1]) && ...);
}
}  // namespace detail
}  // namespace vs

#endif  // VSCGE_INCLUDE_VSCGE_MATH_DETAIL_SWIZZLE_H_