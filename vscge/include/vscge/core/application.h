#ifndef VSCGE_INCLUDE_VSCGE_APPLICATION_H
#define VSCGE_INCLUDE_VSCGE_APPLICATION_H

#include <Windows.h>

#include <vector>

#include "vscge/core/core.h"
#include "vscge/core/renderer.h"
#include "vscge/core/timer.h"
#include "vscge/core/types.h"

namespace vs {
class VS_API Application {
 public:
  Application(const Size &screen_size = {240, 120},
              const Size &font_size = {4, 4});

  void Start();

 private:
  void MainLoop();
  virtual void OnStart(){};
  virtual void OnUpdate(Timestep timestep) = 0;

  HANDLE buffer_in_;
};
}  // namespace vs

#endif  // VSCGE_INCLUDE_VSCGE_APPLICATION_H