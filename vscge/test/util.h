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

#ifndef VSCGE_TEST_UTIL_H_
#define VSCGE_TEST_UTIL_H_

#include <gmock/gmock.h>
#include <gtest/gtest.h>

// Adapted from
// https://stackoverflow.com/questions/28768359/comparison-of-floating-point-arrays-using-google-test-and-google-mock
MATCHER_P(VsFloatNear, tol, "Out of range") {
  return (std::get<0>(arg) > std::get<1>(arg) - tol &&
          std::get<0>(arg) < std::get<1>(arg) + tol);
}

#define EXPECT_VEC_EQ(val1, val2) \
  EXPECT_THAT((val1).data,        \
              ::testing::Pointwise(VsFloatNear(1e-4f), (val2).data))

#endif  // VSCGE_TEST_UTIL_H_
