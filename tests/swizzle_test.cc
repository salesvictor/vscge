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

#include <gtest/gtest.h>

#include "vscge/math/vector.h"

using namespace vs;

TEST(SwizzleTest, VecFromFloat) {
  float f1 = 7.0f;
  float f2 = 10.0f;

  Vec2 v{f1, f1};
  Vec3 w{f1, f2, f1};
  EXPECT_EQ(w.x, v.x);
  EXPECT_EQ(w.xx, v.xx);
  EXPECT_EQ(w.z, v.x);
  EXPECT_EQ(w.zz, v.xx);
  EXPECT_EQ(w.xz, v);
  EXPECT_EQ(w.zx, v);
}

TEST(SwizzleTest, FloatFromVec) {
  Vec2 v{2.0f, 2.0f};

  EXPECT_EQ(v.x, 2.0f);
  EXPECT_EQ(v.y, 2.0f);
  EXPECT_EQ(v.x, v.y);

  v.x += 1;
  EXPECT_EQ(v.x, 3.0f);

  Vec2 p{0.0f, 0.0f};

  p += v;
  EXPECT_EQ(p.x, v.x);
  EXPECT_EQ(p.y, v.y);
}

TEST(SwizzleTest, Vec2) {
  Vec2 v{1.0f, 2.0f};

  Vec2 p = v.xy;
  EXPECT_EQ(p.x, v.x);
  EXPECT_EQ(p.y, v.y);

  Vec2 q = v.xx;
  EXPECT_EQ(q.x, q.y);
  EXPECT_EQ(q.x, v.x);
  EXPECT_EQ(q.y, v.x);

  Vec2 r = v.yy;
  EXPECT_EQ(r.x, r.y);
  EXPECT_EQ(r.x, v.y);
  EXPECT_EQ(r.y, v.y);
}

TEST(SwizzleTest, Vec3) {
  Vec3 v{1.0f, 2.0f, 3.0f};

  Vec3 p = v.xyz;
  EXPECT_EQ(p.x, v.x);
  EXPECT_EQ(p.y, v.y);
  EXPECT_EQ(p.z, v.z);

  Vec3 q = v.xxx;
  EXPECT_EQ(q.x, q.y);
  EXPECT_EQ(q.y, q.z);
  EXPECT_EQ(q.x, v.x);
  EXPECT_EQ(q.y, v.x);
  EXPECT_EQ(q.z, v.x);

  Vec3 r = v.yyy;
  EXPECT_EQ(r.x, r.y);
  EXPECT_EQ(r.y, r.z);
  EXPECT_EQ(r.x, v.y);
  EXPECT_EQ(r.y, v.y);
  EXPECT_EQ(r.z, v.y);
}
