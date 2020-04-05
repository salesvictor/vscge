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

#ifndef VSCGE_INCLUDE_VSCGE_CORE_ENTRY_POINT_H_
#define VSCGE_INCLUDE_VSCGE_CORE_ENTRY_POINT_H_

#include "vscge/api.h"
#include "vscge/core/application.h"
#include "vscge/instrumentation/profiler.h"
#include "vscge/memory/reference.h"

#define VS_REGISTER_APP(app_name)               \
  vs::Ref<vs::Application> vs::CreateApp() {    \
    return vs::CreateRef<app_name>(app_name()); \
  }

namespace vs {
Ref<Application> VS_API CreateApp();

inline int VS_LOCAL main() {
  VS_PROFILE_BEGIN_SESSION("Startup", "startup.json");
  Ref<Application> app = vs::CreateApp();
  VS_PROFILE_END_SESSION();

  app->Initialize();

  return 0;
}
}  // namespace vs

#endif  // VSCGE_INCLUDE_VSCGE_CORE_ENTRY_POINT_H_
