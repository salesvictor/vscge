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

macro(add_example name platform)
  add_executable(
    ${name}
    ${platform}/${name}.cc
  )
  if(${platform} STREQUAL "Windows")
    set_target_properties(${name} PROPERTIES WIN32_EXECUTABLE TRUE)
  endif()
  target_link_libraries(${name} vs::cge)
  set_target_properties(
    ${name} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${VSCGE_ROOT}/examples/${platform}/${name}"
  )

  add_custom_target(${name}_copy)
  add_dependencies(${name}_copy vs::cge)
  add_custom_command(
    TARGET ${name}_copy PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${VSCGE_ROOT}/lib/vscge.lib "${VSCGE_ROOT}/examples/${platform}/${name}"
  )

  add_custom_command(
    TARGET ${name} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:Logger> $<TARGET_FILE_DIR:${name}>
  )
endmacro()

# add_example(game_of_life)
add_example(blank_window "Windows")