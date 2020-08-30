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

#include "vscge/math/vector.h"

#include <gtest/gtest.h>

#include <array>

#include "util.h"

using namespace vs;

TEST(VectorConstructionTest, Float) {
  Vec2 v{};

  EXPECT_EQ(v.x, 0.0f);
  EXPECT_EQ(v.y, 0.0f);
  EXPECT_EQ(v.x, v.y);

  v = 5.0f;
  EXPECT_EQ(v.x, 5.0f);
  EXPECT_EQ(v.y, 5.0f);
  EXPECT_EQ(v.x, v.y);

  Vec2 p{1.0f, 2.0f};
  EXPECT_EQ(p.x, 1.0f);
  EXPECT_EQ(p.y, 2.0f);

  Vec2 q{2.0f, 2.0f};
  EXPECT_EQ(q.x, 2.0f);
  EXPECT_EQ(q.y, 2.0f);

  Vec2 r{-1.0f, -3.0f};
  EXPECT_EQ(r.x, -1.0f);
  EXPECT_EQ(r.y, -3.0f);
}

TEST(VectorConstructionTest, Int) {
  Vec2i v{};

  EXPECT_EQ(v.x, 0);
  EXPECT_EQ(v.y, 0);
  EXPECT_EQ(v.x, v.y);

  v = 5;
  EXPECT_EQ(v.x, 5);
  EXPECT_EQ(v.y, 5);
  EXPECT_EQ(v.x, v.y);

  Vec2i p{1, 2};
  EXPECT_EQ(p.x, 1);
  EXPECT_EQ(p.y, 2);

  Vec2i q{2, 2};
  EXPECT_EQ(q.x, 2);
  EXPECT_EQ(q.y, 2);
}

TEST(VectorDataTest, Float) {
  Vec2 v{1.0f, 2.0f};
  EXPECT_EQ(v.data, (std::array{1.0f, 2.0f}));
}

TEST(VectorTest, Size) {
  EXPECT_EQ(sizeof(Vec2), sizeof(Vec2Base<float>));
  EXPECT_EQ(sizeof(Vec3), sizeof(Vec3Base<float>));
  EXPECT_EQ(sizeof(Vec4), sizeof(Vec4Base<float>));

  EXPECT_EQ(sizeof(Vec2i), sizeof(Vec2Base<int>));
  EXPECT_EQ(sizeof(Vec3i), sizeof(Vec3Base<int>));
  EXPECT_EQ(sizeof(Vec4i), sizeof(Vec4Base<int>));

  EXPECT_EQ(sizeof(Vec2), sizeof(std::array<float, 2>));
  EXPECT_EQ(sizeof(Vec3), sizeof(std::array<float, 3>));
  EXPECT_EQ(sizeof(Vec4), sizeof(std::array<float, 4>));

  EXPECT_EQ(sizeof(Vec2i), sizeof(std::array<int, 2>));
  EXPECT_EQ(sizeof(Vec3i), sizeof(std::array<int, 3>));
  EXPECT_EQ(sizeof(Vec4i), sizeof(std::array<int, 4>));
}

TEST(VectorOperationTest, Add) {
  Vec2 v1{3.0f, 4.0f};
  EXPECT_VEC_EQ(v1 + v1, Vec2(6.0f, 8.0f));
  EXPECT_VEC_EQ(v1, Vec2(3.0f, 4.0f));

  Vec2 v2{7.0f, 6.0f};
  EXPECT_VEC_EQ(v1 + v2, Vec2(10.0f, 10.0f));
  EXPECT_VEC_EQ(v1, Vec2(3.0f, 4.0f));
  EXPECT_VEC_EQ(v2, Vec2(7.0f, 6.0f));

  Vec2 v3{-6.0f, -8.0f};
  EXPECT_VEC_EQ(v1 + v1 + v3, Vec2{});
  EXPECT_VEC_EQ(v1, Vec2(3.0f, 4.0f));
  EXPECT_VEC_EQ(v3, Vec2(-6.0f, -8.0f));
}

TEST(VectorOperationTest, Subtract) {
  Vec2 v1{3.0f, 4.0f};
  EXPECT_VEC_EQ(v1 - v1, Vec2{});

  Vec2 v2{-3.0f, -4.0f};
  EXPECT_VEC_EQ(v1 - v2, Vec2(6.0f, 8.0f));
}
