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

file(GLOB         ${module}_sources RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} CONFIGURE_DEPENDS "src/*.cc")
file(GLOB_RECURSE ${module}_headers RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} CONFIGURE_DEPENDS "include/vscge/${module}/*.h")

vscge_debug("SOURCES::${module}_headers:: ${${module}_headers}")
vscge_debug("SOURCES::${module}_sources:: ${${module}_sources}")

target_sources(
  ${module}
  PUBLIC  ${${module}_headers}
  PRIVATE ${${module}_sources}
)

vscge_find_dependencies(${module}_headers ${module}_headers_deps)
vscge_find_dependencies(${module}_sources ${module}_sources_deps)

vscge_separate_dependencies(
  ${module}_headers_deps ${module}_sources_deps
  ${module}_public_deps ${module}_interface_deps ${module}_private_deps
)

vscge_debug("DEPS::${module}_public_deps::    ${${module}_public_deps}")
vscge_debug("DEPS::${module}_interface_deps:: ${${module}_interface_deps}")
vscge_debug("DEPS::${module}_private_deps::   ${${module}_private_deps}")

vscge_target_sources_platform(${module} ${module}_platform_sources)
vscge_find_dependencies(${module}_platform_sources ${module}_platform_deps)

target_link_libraries(
  ${module}
  INTERFACE ${${module}_interface_deps}
  PUBLIC    ${${module}_public_deps}
  PRIVATE   ${${module}_private_deps} ${${module}_platform_deps}
)
