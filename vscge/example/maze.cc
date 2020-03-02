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

#include <vscge/vscge.h>

#include <string>


std::wstring map =
    L"#########......."
    L"#..............."
    L"#.......########"
    L"#..............#"
    L"#......##......#"
    L"#......##......#"
    L"#..............#"
    L"###...@........#"
    L"##.............#"
    L"#......####..###"
    L"#......#.......#"
    L"#......#.......#"
    L"#..............#"
    L"#......#########"
    L"#..............#"
    L"################";

class ExampleGame : public vs::Application {
 private:
  virtual void OnStart() override {
    for (auto &ch : screen_) {
      ch = (ch == '#') ? vs::PixelBlock::kFull
                       : (ch == '.') ? vs::PixelBlock::kLightShade
                                     : vs::PixelBlock::kLargeBlackCircle;
    }

    vs::Renderer::DrawBuffer(vs::StringToPixelBuffer(screen_, {0, 0, 16, 16}));
  }
  virtual void OnUpdate(const vs::Timestep &timestep) override {
    // vs::Renderer::DrawBuffer(vs::StringToPixelBuffer(screen_, {0, 0, 16,
    // 16}));
  }

 public:
  std::wstring screen_;
};

int main() {
  ExampleGame game;

  game.screen_ = map;
  game.Start();

  return 0;
}