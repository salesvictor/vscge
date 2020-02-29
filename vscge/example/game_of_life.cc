#include <vscge/vscge.h>

#include <string>
#include <thread>


class GameOfLife : public vs::Application {
 private:
  virtual void OnStart() override {
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
  }

  virtual void OnUpdate(vs::Timestep timestep) override {
    if (1 / timestep > 60) {
      std::this_thread::sleep_for(
          std::chrono::duration<float>{1. / 60 - timestep});
    }
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
          pixel.Char() = L' ';
          pixel.Color() = vs::PixelColor{vs::PixelColor::BG::kBlack};
        }
      }
    }

    vs::Renderer::DrawBuffer(new_state);
  }
};

int main() {
  GameOfLife game;
  game.Start();
  return 0;
}