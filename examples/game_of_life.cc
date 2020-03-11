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

#include <vscge/instrumentation/profiler.h>
#include <vscge/vscge.h>

#include <string>

class GameOfLife : public vs::Application {
 protected:
  virtual void OnStart() override {
    VS_PROFILE_FUNCTION();
    vs::Rect window_rect = vs::Renderer::GetWindowRect();
    current_state_.clear();
    current_state_.reserve(window_rect.BufferSize());

    std::string initial_state_str =
        "........................#............"
        "......................#.#............"
        "............##......##............##."
        "...........#...#....##............##."
        "##........#.....#...##..............."
        "##........#...#.##....#.#............"
        "..........#.....#.......#............"
        "...........#...#....................."
        "............##.......................";

    std::unordered_map<char, vs::PixelProps> char_map = {
        {'.', {vs::PixelColor::FG::kBlack, vs::PixelBlock::kEmpty}},
        {'#', {vs::PixelColor::BG::kWhite, vs::PixelBlock::kFull}}};

    for (int x = 0; x < window_rect.width; ++x) {
      for (int y = 0; y < window_rect.height; ++y) {
        if (x == 0 || x == window_rect.width - 1 || y == 0 ||
            y == window_rect.height - 1) {
          current_state_.emplace_back(
              vs::Pixel({x, y}, vs::PixelProps(vs::PixelBlock::kDarkShade)));
        } else {
          current_state_.emplace_back(vs::Pixel({x, y}, {}));
        }
      }
    }
    std::vector<vs::Pixel> glider_gun =
        vs::StringToPixelBuffer(initial_state_str, {10, 10, 37, 9}, char_map);

    current_state_.insert(current_state_.end(), glider_gun.begin(),
                          glider_gun.end());

    vs::Renderer::DrawBuffer(current_state_);

    running_ = false;
  }

  virtual void OnEvent(vs::Ref<vs::Event> event) override {
    VS_PROFILE_FUNCTION();
    vs::EventDispatcher dispatcher{event};
    dispatcher.Dispatch<vs::KeyPressedEvent>(VS_BIND_EVENT(OnKeyPress));
    dispatcher.Dispatch<vs::MouseButtonPressedEvent>(
        VS_BIND_EVENT(OnMouseClick));
    dispatcher.Dispatch<vs::MouseMovedEvent>(VS_BIND_EVENT(OnMouseClick));
  }

  void OnKeyPress(vs::Ref<vs::KeyPressedEvent> key_event) {
    if (key_event->key == vs::Key::kSpace) {
      vs::Logger::Log("OnKeyPress for Space");
      running_ = !running_;
    } else if (!running_ && key_event->key == vs::Key::kEscape) {
      OnStart();
    }
  }

  void OnMouseClick(vs::Ref<vs::MouseEvent> mouse_event) {
    if (!running_ && mouse_event->buttons.left) {
      vs::Logger::Log("OnMouseClick for Left Button");
      constexpr vs::PixelProps full_white = {{vs::PixelColor::BG::kWhite},
                                             vs::PixelBlock::kFull};
      vs::Renderer::DrawPixel(
          vs::Pixel(vs::Point{mouse_event->x, mouse_event->y}, full_white));
    }
  }

  virtual void OnUpdate(const vs::Timestep &timestep) override {
    if (running_) {
      VS_PROFILE_FUNCTION();
      std::vector<vs::Pixel> new_state = current_state_;

      auto is_alive = [](const vs::PixelProps &props) {
        return props.block == vs::PixelBlock::kFull;
      };

      auto alive_count = [is_alive](int x, int y) {
        constexpr int dx[] = {-1, -1, 0, 1, 1, 1, 0, -1};
        constexpr int dy[] = {0, -1, -1, -1, 0, 1, 1, 1};

        int count = 0;
        vs::Rect window_rect = vs::Renderer::GetWindowRect();
        for (int i = 0; i < 8; i++) {
          vs::Point neibourgh = {x + dx[i], y + dy[i]};
          if (!window_rect.Contains(neibourgh)) {
            continue;
          }

          count += is_alive(vs::Renderer::GetPixelPropsAt(neibourgh));
        }

        return count;
      };

      {
        VS_PROFILE_SCOPE("Calculating New State");
        for (auto &pixel : new_state) {
          vs::PixelBlock block = pixel.Char();
          int x = pixel.x;
          int y = pixel.y;
          int count = alive_count(x, y);

          if (block == vs::PixelBlock::kEmpty) {
            if (count == 3) {
              pixel.Char() = vs::PixelBlock::kFull;
              pixel.Color() = vs::PixelColor{vs::PixelColor::BG::kWhite};
            }
          } else if (block == vs::PixelBlock::kFull) {
            if (count < 2 || count > 3) {
              pixel.Char() = vs::PixelBlock::kEmpty;
              pixel.Color() = vs::PixelColor(vs::PixelColor::BG::kBlack);
            }
          }
        }
      }

      vs::Renderer::DrawBuffer(new_state);
      current_state_ = new_state;
    }
  }

 private:
  bool running_;
  std::vector<vs::Pixel> current_state_;
};

VS_REGISTER_APP(GameOfLife);
