# Copyright 2020 Victor Sales
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      https://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

vscge_check("Configuring external dependencies")

set(${PROJECT_NAME}_FETCHCONTENT_BASE_DIR ${VSCGE_ROOT}/tmp/extern)

vscge_add_external(OpenGL)
vscge_add_external(Gl3w)

if(BUILD_VSCGE_TESTS)
  vscge_add_external(GoogleTest)
endif()

vscge_pass()
