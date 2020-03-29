# Copyright 2020 Victor Sales
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

vscge_check("Configuring Windows Platform")

set(
  VSCGE_SOURCE
  ${VSCGE_SOURCE}
  src/platform/windows/core/entry_point.cc
  src/platform/windows/core/window.cc
  src/platform/windows/logger/logger.cc
  PARENT_SCOPE
)

vscge_pass()
