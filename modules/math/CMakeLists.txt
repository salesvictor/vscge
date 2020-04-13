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
  math
  INTERFACE
    include/vscge/math/matrix.h
    include/vscge/math/vector.h
    include/vscge/math/detail/swizzle.h
)

vscge_add_module_test(
  math
  test
)

find_package(Python3 COMPONENTS Interpreter)
add_custom_target(
  swizzle_generator
  COMMAND ${Python3_EXECUTABLE} ${VSCGE_SOURCE_ROOT}/tool/swizzle_include_generator.py 1 > ${CMAKE_CURRENT_SOURCE_DIR}/include/vscge/math/detail/swizzle_vec1.inc
  COMMAND ${Python3_EXECUTABLE} ${VSCGE_SOURCE_ROOT}/tool/swizzle_include_generator.py 2 > ${CMAKE_CURRENT_SOURCE_DIR}/include/vscge/math/detail/swizzle_vec2.inc
  COMMAND ${Python3_EXECUTABLE} ${VSCGE_SOURCE_ROOT}/tool/swizzle_include_generator.py 3 > ${CMAKE_CURRENT_SOURCE_DIR}/include/vscge/math/detail/swizzle_vec3.inc
  COMMAND ${Python3_EXECUTABLE} ${VSCGE_SOURCE_ROOT}/tool/swizzle_include_generator.py 4 > ${CMAKE_CURRENT_SOURCE_DIR}/include/vscge/math/detail/swizzle_vec4.inc
  COMMENT "Building swizzles"
  DEPENDS ${VSCGE_SOURCE_ROOT}/tool/swizzle_include_generator.py
  VERBATIM
)

add_dependencies(math swizzle_generator)
