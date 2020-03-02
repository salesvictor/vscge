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

class GameOfLife : public vs::Application {
 private:
  virtual void OnStart() override {
    vs::Renderer::ClearScreen();

    std::wstring initial_state =
        L"........................#............"
        L"......................#.#............"
        L"............##......##............##."
        L"...........#...#....##............##."
        L"##........#.....#...##..............."
        L"##........#...#.##....#.#............"
        L"..........#.....#.......#............"
        L"...........#...#....................."
        L"............##.......................";

    for (auto &ch : initial_state)
      ch = (ch == '#') ? vs::PixelBlock::kFull : vs::PixelBlock::kEmpty;

    vs::Renderer::DrawBuffer(
        vs::StringToPixelBuffer(initial_state, {10, 10, 37, 9}));

    vs::Renderer::DrawRect(vs::Renderer::GetWindowRect(),
                           vs::PixelBlock::kDarkShade);

    running_ = false;
  }

  virtual void OnEvent(vs::Ref<vs::Event> event) {
    vs::EventDispatcher dispatcher{event};
    dispatcher.Dispatch<vs::KeyEvent>(VS_BIND_EVENT(OnKeyPress));
    dispatcher.Dispatch<vs::MouseEvent>(VS_BIND_EVENT(OnMouseClick));
  }

  void OnKeyPress(vs::Ref<vs::KeyEvent> key_event) {
    if (key_event->is_down) {
      if (key_event->key == vs::Key::kSpace) {
        running_ = !running_;
      } else if (!running_ && key_event->key == vs::Key::kEscape) {
        OnStart();
      }
    }
  }

  void OnMouseClick(vs::Ref<vs::MouseEvent> mouse_event) {
    if (!running_ && mouse_event->button == vs::MouseButton::kLeft) {
      constexpr vs::PixelProps full_white = {{vs::PixelColor::BG::kWhite},
                                             vs::PixelBlock::kFull};
      vs::Renderer::DrawPixel(
          vs::Pixel(vs::Point{mouse_event->x, mouse_event->y}, full_white));
    }
  }

  virtual void OnUpdate(const vs::Timestep &timestep) override {
    if (running_) {
      std::vector<vs::Pixel> new_state = vs::Renderer::GetBuffer();

      auto is_alive = [](const vs::Pixel &pixel) {
        return pixel.Char() == vs::PixelBlock::kFull;
      };

      auto alive_count = [this, is_alive](short x, short y) {
        constexpr short dx[] = {-1, -1, 0, 1, 1, 1, 0, -1};
        constexpr short dy[] = {0, -1, -1, -1, 0, 1, 1, 1};

        int count = 0;
        vs::Rect window_rect = vs::Renderer::GetWindowRect();
        for (int i = 0; i < 8; i++) {
          vs::Point neibourgh = {x + dx[i], y + dy[i]};
          if (!window_rect.Contains(neibourgh)) {
            continue;
          }

          count += is_alive(vs::Renderer::GetPixelAt(neibourgh));
        }

        return count;
      };

      for (auto &pixel : new_state) {
        wchar_t ch = pixel.Char();
        short x = pixel.x;
        short y = pixel.y;
        int count = alive_count(x, y);

        if (ch == vs::PixelBlock::kEmpty) {
          if (count == 3) {
            pixel.Char() = vs::PixelBlock::kFull;
            pixel.Color() = vs::PixelColor{vs::PixelColor::BG::kWhite};
          }
        } else if (ch == vs::PixelBlock::kFull) {
          if (count < 2 || count > 3) {
            pixel.Char() = vs::PixelBlock::kEmpty;
            pixel.Color() = vs::PixelColor{vs::PixelColor::BG::kBlack};
          }
        }
      }

      vs::Renderer::DrawBuffer(new_state);
    }
  }

 private:
  bool running_;
};

int main() {
  GameOfLife game;
  game.Start();
  return 0;
}