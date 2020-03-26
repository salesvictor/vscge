#include "vscge/core/application.h"
#include "vscge/core/core.h"
#include "vscge/instrumentation/profiler.h"

int main() {
  VS_PROFILE_BEGIN_SESSION("Startup", "startup.json");
  vs::Ref<vs::Application> app = vs::CreateApp();
  VS_PROFILE_END_SESSION();

  app->Start();
  return 0;
}