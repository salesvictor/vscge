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

#ifndef VSCGE_INCLUDE_VSCGE_MATH_TRANSFORM_H_
#define VSCGE_INCLUDE_VSCGE_MATH_TRANSFORM_H_

#include <array>

#include "vscge/math/matrix.h"
#include "vscge/math/vector.h"

namespace vs {
template <typename Elem, std::size_t size>
Matrix<Elem, size, size> IdentityMatrix() {
  std::array<Elem, size> diag;
  diag.fill(1);

  Matrix<Elem, size, size> mat{};
  mat.SetPrimaryDiag(diag);
  return mat;
}

Mat4 IdMat4() { return IdentityMatrix<float, 4>(); }

Mat4 ScaleMatrix(const Vec3& scale) {
  Mat4 matrix  = IdMat4();
  matrix(0, 0) = scale.x;
  matrix(1, 1) = scale.y;
  matrix(2, 2) = scale.z;
  return matrix;
}

Vec4 Scale(const Vec4& vec, const Vec3& scale) {
  Mat4 transform = ScaleMatrix(scale);
  return transform * vec;
}

Mat4 TranslationMatrix(const Vec3& translation) {
  Mat4 matrix  = IdMat4();
  matrix(0, 3) = translation.x;
  matrix(1, 3) = translation.y;
  matrix(2, 3) = translation.z;
  return matrix;
}

Vec4 Translate(const Vec4& vec, const Vec3& translation) {
  Mat4 transform = TranslationMatrix(translation);
  return transform * vec;
}
}  // namespace vs

#endif  // VSCGE_INCLUDE_VSCGE_MATH_TRANSFORM_H_
