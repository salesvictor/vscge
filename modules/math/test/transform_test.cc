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

#include "vscge/math/transform.h"

#include <gtest/gtest.h>

// TODO(Victor): Disabling these for now, check if really should
#pragma warning(disable : 4244)

using namespace vs;

TEST(TransformTest, Scale) {
  Vec4 v{};
  v = 1.0f;

  Vec3 scale{};
  scale  = 2.0f;
  Vec4 w = Scale(v, scale);

  EXPECT_EQ(w.x, 2.0f);
  EXPECT_EQ(w.y, 2.0f);
  EXPECT_EQ(w.z, 2.0f);
  EXPECT_EQ(w.w, 1.0f);

  scale = 0.5f;
  w     = Scale(w, scale);

  EXPECT_EQ(w.x, 1.0f);
  EXPECT_EQ(w.y, 1.0f);
  EXPECT_EQ(w.z, 1.0f);
  EXPECT_EQ(w.w, 1.0f);
}

TEST(TransformTest, Translate) {
  Vec4 v{};
  v = 1.0f;

  Vec3 trans{};
  trans  = 2.0f;
  Vec4 w = Translate(v, trans);

  EXPECT_EQ(w.x, 3.0f);
  EXPECT_EQ(w.y, 3.0f);
  EXPECT_EQ(w.z, 3.0f);
  EXPECT_EQ(w.w, 1.0f);

  trans = -2.0f;
  w     = Translate(w, trans);

  EXPECT_EQ(w.x, 1.0f);
  EXPECT_EQ(w.y, 1.0f);
  EXPECT_EQ(w.z, 1.0f);
  EXPECT_EQ(w.w, 1.0f);
}