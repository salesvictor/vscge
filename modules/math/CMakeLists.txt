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
    include/vscge/math/transform.h
    include/vscge/math/vector.h
    include/vscge/math/detail/swizzle.h
)

vscge_add_module_test(
  math
  test
)

find_package(Python3 COMPONENTS Interpreter)

set(
  swizzle_includes
  ${CMAKE_CURRENT_SOURCE_DIR}/include/vscge/math/detail/swizzle_vec1.inc
  ${CMAKE_CURRENT_SOURCE_DIR}/include/vscge/math/detail/swizzle_vec2.inc
  ${CMAKE_CURRENT_SOURCE_DIR}/include/vscge/math/detail/swizzle_vec3.inc
  ${CMAKE_CURRENT_SOURCE_DIR}/include/vscge/math/detail/swizzle_vec4.inc
)

set(swizzle_generator_py ${VSCGE_SOURCE_ROOT}/tool/swizzle_include_generator.py)

# This is a clever way of dealing with this, the command will only run if the
# dependency -- i.e. the python generator -- changes (this doesn't work for)
# targets for some reason.
#
# By adding the output of this command to the swizzle_generator target, we make
# it run when the target is built.
add_custom_command(
  OUTPUT ${swizzle_includes}
  COMMAND ${Python3_EXECUTABLE} ${swizzle_generator_py} 1 > ${CMAKE_CURRENT_SOURCE_DIR}/include/vscge/math/detail/swizzle_vec1.inc
  COMMAND ${Python3_EXECUTABLE} ${swizzle_generator_py} 2 > ${CMAKE_CURRENT_SOURCE_DIR}/include/vscge/math/detail/swizzle_vec2.inc
  COMMAND ${Python3_EXECUTABLE} ${swizzle_generator_py} 3 > ${CMAKE_CURRENT_SOURCE_DIR}/include/vscge/math/detail/swizzle_vec3.inc
  COMMAND ${Python3_EXECUTABLE} ${swizzle_generator_py} 4 > ${CMAKE_CURRENT_SOURCE_DIR}/include/vscge/math/detail/swizzle_vec4.inc
  DEPENDS ${swizzle_generator_py}
  VERBATIM
)
add_custom_target(
  swizzle_generator ALL
  COMMENT "Building swizzles"
  DEPENDS ${swizzle_includes}
  VERBATIM
)

add_dependencies(math swizzle_generator)