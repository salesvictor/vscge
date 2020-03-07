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

#ifndef VSCGE_INCLUDE_VSCGE_VERSION_H_
#define VSCGE_INCLUDE_VSCGE_VERSION_H_

#define VSCGE_VERSION_MAJOR 0
#define VSCGE_VERSION_MINOR 6
#define VSCGE_VERSION_PATCH 0

#define VSCGE_STR(str) VSCGE_STR_IMPL(str)
#define VSCGE_STR_IMPL(str) #str

#define VSCGE_VERSION            \
  VSCGE_STR(VSCGE_VERSION_MAJOR) \
  "." VSCGE_STR(VSCGE_VERSION_MINOR) "." VSCGE_STR(VSCGE_VERSION_PATCH)

#endif  // VSCGE_INCLUDE_VSCGE_VERSION_H_
