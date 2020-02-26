#include <vscge/application.h>
#include <vscge/utils/conversions.h>

#include <string>

std::wstring map = 
	L"#########......."
	L"#..............."
	L"#.......########"
	L"#..............#"
	L"#......##......#"
	L"#......##......#"
	L"#..............#"
	L"###............#"
	L"##.............#"
	L"#......####..###"
	L"#......#.......#"
	L"#......#.......#"
	L"#..............#"
	L"#......#########"
	L"#..............#"
	L"################";

class ExampleGame : public vs::Application {
 protected:
  virtual void OnUpdate() override {
    DrawBuffer(vs::StringToPixelBuffer(screen_, {0, 0, 16, 16}));
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