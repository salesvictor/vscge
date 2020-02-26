#ifndef VSCGE_INCLUDE_APPLICATION_H
#define VSCGE_INCLUDE_APPLICATION_H

#include "vscge/core/types.h"

#include <vector>

#include <Windows.h>

namespace vs {
class Application {
 public:
  Application(const Size &screen_size = {80, 60}, const Size &font_size = {8, 8});

  void Start();
  void SetPixel(const Pixel &pixel);
  void DrawBuffer(const std::vector<Pixel> &buffer);
  void DrawLine(const Point &p1, const Point &p2);
  void DrawRect(const Rect &rect);

 protected:
  std::vector<Pixel> screen_buffer_;
  Size screen_size_;
  Rect window_;

  virtual void OnStart() {};
  virtual void OnUpdate() = 0;

 private:
  Size font_size_;

  HANDLE buffer_in_;
  HANDLE buffer_out_;


  void MainLoop();
};
} // namespace vs

#endif // VSCGE_INCLUDE_APPLICATION_H