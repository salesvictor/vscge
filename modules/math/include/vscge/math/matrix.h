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

#include "vscge/api.h"
#include "vscge/core/types.h"
#include "vscge/math/detail/swizzle.h"
#include "vscge/math/vector.h"

namespace vs {
enum class MatrixOrdering {
  kColumnMajor,
  kRowMajor,
};

template <class Elem, std::size_t rows, std::size_t columns,
          MatrixOrdering ordering = MatrixOrdering::kColumnMajor>
class VS_API Matrix {
 public:
  Matrix() = default;
  Matrix(const Elem& default_elem) : Matrix(rows, cols) {
    data_.fill(default_elem);
  }

  Elem& operator()(std::size_t row, std::size_t col) {
    return const_cast<Elem&>(std::as_const(*this)(row, col));
  }
  const Elem& operator()(std::size_t row, std::size_t col) const {
    if constexpr (ordering == MatrixOrdering::kColumnMajor) {
      return data_[col * size_.width + row];
    } else {
      return data_[row * size_.width + col];
    }
  }

  Elem& operator()(Point location) { return (*this)(location.x, location.y); }
  const Elem& operator()(Point location) const {
    return (*this)(location.x, location.y);
  }

  Elem& At(std::size_t row, std::size_t col) { return (*this)(row, col); }
  const Elem& At(std::size_t row, std::size_t col) const {
    return (*this)(row, col);
  }

  auto Buffer() const { return data_.data(); }

  constexpr static std::size_t SmallerDim() {
    return rows < columns ? rows : columns;
  }

  Matrix& SetPrimaryDiag(const std::array<Elem, SmallerDim()>& diag) {
    for (std::size_t i = 0; i < SmallerDim(); ++i) {
      At(i, i) = diag[i];
    }

    return *this;
  }

  template <template <typename> class VecT, class VecElem, std::size_t... idxs>
  VecBase<Elem, rows> operator*(
      const detail::Swizzle<VecT, VecElem, idxs...>& vec) {
    static_assert(columns == sizeof...(idxs),
                  "Incompatible sizes for multiplication!");
    VecBase<Elem, rows> vec_result;
    for (std::size_t row = 0; row < rows; ++row) {
      Elem row_result = 0;
      for (std::size_t col = 0; col < columns; ++col) {
        row_result += At(row, col) * vec[col];
      }
      vec_result[row] = row_result;
    }

    return vec_result;
  }

 private:
  Size size_ = {rows, columns};
  std::array<Elem, rows * columns> data_;
};

template <class Elem>
using Mat2Base = Matrix<Elem, 2, 2>;
using Mat2     = Mat2Base<float>;

template <class Elem>
using Mat3Base = Matrix<Elem, 3, 3>;
using Mat3     = Mat3Base<float>;

template <class Elem>
using Mat4Base = Matrix<Elem, 4, 4>;
using Mat4     = Mat4Base<float>;

template <class Elem>
using Mat34Base = Matrix<Elem, 3, 4>;
using Mat34     = Mat34Base<float>;

template <class Elem>
using Mat43Base = Matrix<Elem, 4, 3>;
using Mat43     = Mat43Base<float>;
}  // namespace vs

#endif  // VSCGE_INCLUDE_VSCGE_MATH_MATRIX_H_
