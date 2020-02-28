#ifndef VSCGE_INCLUDE_VSCGE_APPLICATION_H
#define VSCGE_INCLUDE_VSCGE_APPLICATION_H

#include <Windows.h>

#include <vector>

#include "vscge/core/timer.h"
#include "vscge/core/types.h"

namespace vs {
class Application {
 public:
  Application(const Size &screen_size = {240, 120},
              const Size &font_size = {4, 4});

  void Start();
  void SetPixel(const Pixel &pixel);
  void DrawBuffer(const std::vector<Pixel> &buffer);
  void DrawLine(const Point &p1, const Point &p2);
  void DrawRect(const Rect &rect);

 protected:
  std::vector<Pixel> screen_buffer_;
  Size screen_size_;
  Rect window_;

  virtual void OnStart(){};
  virtual void OnUpdate(Timestep timestep) = 0;

 private:
  Size font_size_;

  HANDLE buffer_in_;
  HANDLE buffer_out_;

  SMALL_RECT window_wrapper_;

  void MainLoop();
};
}  // namespace vs

#endif  // VSCGE_INCLUDE_VSCGE_APPLICATION_H