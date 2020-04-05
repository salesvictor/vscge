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

#ifndef VSCGE_INCLUDE_VSCGE_MATH_VECTOR_H_
#define VSCGE_INCLUDE_VSCGE_MATH_VECTOR_H_

#include <array>

#include "vscge/api.h"
#include "vscge/math/detail/swizzle.h"

namespace vs {
// Forward declaration of all vector types.
template <class Elem>
struct VS_API Vec2Base;
template <class Elem>
struct VS_API Vec3Base;
template <class Elem>
struct VS_API Vec4Base;

// TODO(Victor): I tried creating a base vector class that had variadic
// constructors for all vectors, but it wasn't working.
template <class Elem>
struct VS_API Vec2Base : public detail::Swizzle<Vec2Base, Elem, 0, 1> {
  Vec2Base() = default;
  Vec2Base(Elem x, Elem y) : data{x, y} {}
  Vec2Base(const Vec2Base& other) : data{other.data} {}

  template <std::size_t... idxs>
  Vec2Base(const detail::Swizzle<Vec2Base, Elem, idxs...>& swizzle) {
    static_assert(sizeof...(idxs) == 2, "Too many indices in swizzle!");

    std::size_t own_index = 0;
    ((data[own_index++] = swizzle[idxs]), ...);
  }

  union {
    std::array<Elem, 2> data;
#include "vscge/math/detail/swizzle_vec1.inc"
#include "vscge/math/detail/swizzle_vec2.inc"
  };
};

using Vec2  = Vec2Base<float>;
using Vec2i = Vec2Base<int>;

template <class Elem>
struct VS_API Vec3Base : public detail::Swizzle<Vec3Base, Elem, 0, 1, 2> {
  Vec3Base() = default;
  Vec3Base(Elem x, Elem y, Elem z) : data{x, y, z} {}
  Vec3Base(const Vec3Base& other) : data{other.data} {}

  template <std::size_t... idxs>
  Vec3Base(const detail::Swizzle<Vec3Base, Elem, idxs...>& swizzle) {
    static_assert(sizeof...(idxs) == 3, "Too many indices in swizzle!");

    std::size_t own_index = 0;
    ((data[own_index++] = swizzle[idxs]), ...);
  }

  union {
    std::array<Elem, 3> data;
#include "vscge/math/detail/swizzle_vec1.inc"
#include "vscge/math/detail/swizzle_vec2.inc"
#include "vscge/math/detail/swizzle_vec3.inc"
  };
};

using Vec3  = Vec3Base<float>;
using Vec3i = Vec3Base<int>;

template <class Elem>
struct VS_API Vec4Base : public detail::Swizzle<Vec4Base, Elem, 0, 1, 2, 3> {
  Vec4Base() = default;
  Vec4Base(Elem x, Elem y, Elem z, Elem w) : data{x, y, z, w} {}
  Vec4Base(const Vec4Base& other) : data{other.data} {}

  template <std::size_t... idxs>
  Vec4Base(const detail::Swizzle<Vec4Base, Elem, idxs...>& swizzle) {
    static_assert(sizeof...(idxs) == 4, "Too many indices in swizzle!");

    std::size_t own_index = 0;
    ((data[own_index++] = swizzle[idxs]), ...);
  }
  union {
    std::array<Elem, 4> data;
#include "vscge/math/detail/swizzle_vec1.inc"
#include "vscge/math/detail/swizzle_vec2.inc"
#include "vscge/math/detail/swizzle_vec3.inc"
#include "vscge/math/detail/swizzle_vec4.inc"
  };
};

using Vec4  = Vec4Base<float>;
using Vec4i = Vec4Base<int>;
}  // namespace vs

#endif  // VSCGE_INCLUDE_VSCGE_MATH_VECTOR_H_
