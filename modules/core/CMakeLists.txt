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

target_sources(
  core
  PUBLIC
    include/vscge/core/application.h
    include/vscge/core/entry_point.h
    include/vscge/core/renderer.h
    include/vscge/core/shader.h
    include/vscge/core/timer.h
    include/vscge/core/types.h
    include/vscge/core/window.h
  PRIVATE
    src/application.cc
    src/renderer.cc
    src/shader.cc
    src/timer.cc
)

vscge_target_sources_platform(
  core
  entry_point.cc
  window.cc
)

find_package(OpenGL REQUIRED)
# TODO(Victor): Find a better way to do this 
# find_package(gl3w REQUIRED)

target_link_libraries(
  core
  PUBLIC
    vs::math
    vs::event
    vs::instrumentation
    vs::debug
    vs::logger
    vs::util
    OpenGL::GL
  PRIVATE
    gl3w
)
