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

#ifndef VSCGE_INCLUDE_VSCGE_MATH_MATRIX_H_
#define VSCGE_INCLUDE_VSCGE_MATH_MATRIX_H_

#include <array>

#include "vscge/core/api.h"
#include "vscge/core/types.h"

namespace vs {
enum class MatrixOrdering {
  kColumnMajor,
  kRowMajor,
};

template <class Elem, int rows, int columns,
          MatrixOrdering ordering = MatrixOrdering::kColumnMajor>
class VS_API Matrix {
 public:
  Matrix() = default;
  Matrix(const Elem& default_elem) : Matrix(rows, cols) {
    data_.fill(default_elem);
  }

  Elem& operator()(int row, int col) {
    return const_cast<Elem&>(std::as_const(*this)(row, col));
  }
  const Elem& operator()(int row, int col) const {
    if constexpr (ordering == MatrixOrdering::kColumnMajor) {
      return data_[col * size_.width + row];
    } else {
      return data_[row * size_.width + col];
    }
  }

  Elem& operator()(Point location) { return (*this)(location.y, location.x); }
  const Elem& operator()(Point location) const {
    return (*this)(location.x, location.y);
  }

  const std::vector<Elem>& Buffer() const { return data_; }

 private:
  constexpr Size size_ = {rows, columns};
  std::array<Elem, size_.Area()> data_;
};

template <class Elem>
using Mat3_ = Matrix<Elem, 3, 3>;
using Mat3  = Mat3_<float>;

template <class Elem>
using Mat4_ = Matrix<Elem, 4, 4>;
using Mat4  = Mat4_<float>;
}  // namespace vs

#endif  // VSCGE_INCLUDE_VSCGE_MATH_MATRIX_H_
