// Copyright 2020 Victor Sales
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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