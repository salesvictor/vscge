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

macro(vscge_add_module module)
  vscge_check("Configuring vs::${module}")
  set(HEADER_ONLY memory util math event)
  set(INTERFACE_OR_PUBLIC "PUBLIC")
  unset(MODULE_TYPE)
  if(${module} IN_LIST HEADER_ONLY)
    set(MODULE_TYPE "INTERFACE")
    set(INTERFACE_OR_PUBLIC "INTERFACE")
  endif()
  add_library(${module} ${MODULE_TYPE})
  target_compile_features(${module} ${INTERFACE_OR_PUBLIC} cxx_std_17)
  target_include_directories(
    ${module}
    ${INTERFACE_OR_PUBLIC}
      ${module}/include/
    ${INTERFACE_OR_PUBLIC} $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${module}/include>
    ${INTERFACE_OR_PUBLIC} $<INSTALL_INTERFACE:${module}/include>
  )
  target_include_directories(${module} ${INTERFACE_OR_PUBLIC} ${VSCGE_SOURCE_ROOT}/include)
  if(NOT "${MODULE_TYPE}" STREQUAL "INTERFACE")
    vscge_add_analyzers(${module})
    set_target_properties(
      ${module} PROPERTIES
      VERSION ${PROJECT_VERSION}
      ARCHIVE_OUTPUT_DIRECTORY ${VSCGE_ROOT}/lib
      LIBRARY_OUTPUT_DIRECTORY ${VSCGE_ROOT}/lib
      RUNTIME_OUTPUT_DIRECTORY ${VSCGE_ROOT}/bin
    )
  endif()
  vscge_add_subdir(${module})
  add_library(vs::${module} ALIAS ${module})
  target_link_libraries(vscge INTERFACE vs::${module})
  vscge_pass()
endmacro()

macro(vscge_target_sources_platform target platform_sources)
  if(VS_TARGET_PLATFORM STREQUAL "Windows")
    set(platform_folder src/platform/windows)
  elseif(VS_TARGET_PLATFORM STREQUAL "Windows Console")
    set(platform_folder src/platform/windows_console)
  endif()

  file(GLOB ${platform_sources} RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} CONFIGURE_DEPENDS "${platform_folder}/*.cc")

  vscge_debug("PLATFORM::${${platform_sources}}")

  target_sources(${target} PRIVATE ${${platform_sources}})
endmacro()

macro(vscge_find_dependencies _sources deps)
  # _sources is a list name
  set(sources ${${_sources}})
  # Parenthesis use for grouping
  set(module_regex "^#include \"vscge/(.+)/.+\.h")
  foreach(source ${sources})
    # Gets all vscge include lines
    file(STRINGS ${source} dependencies_lines REGEX ${module_regex} )
    foreach(line ${dependencies_lines})
      # For some reason, REGEX REPLACE was giving an extra >"< to the output,
      # so we do just a regular match here
      string(REGEX MATCH ${module_regex} _ ${line})

      # Gets the match of the group in the regex, which should be a module.
      # Must add "vs::" here because some libs have keyword names (i.e. debug).
      set(dependency "vs::${CMAKE_MATCH_1}")

      # I tried to make the regex work as intended to only get the module name,
      # alas, it didn't work, so we do a manual split here
      string(REPLACE "/" ";" dirs ${dependency})
      list(GET dirs 0 dependency)
      list(APPEND dependencies ${dependency})
    endforeach()

    # Checks for gl3w
    file(STRINGS ${source} gl3w_lines REGEX "^#include <.*/gl3w.h")
    list(LENGTH gl3w_lines gl3w_lines_size)
    if(${gl3w_lines_size} GREATER_EQUAL 1)
      list(APPEND dependencies gl3w)
    endif()
  endforeach()

  list(SORT dependencies)
  list(REMOVE_DUPLICATES dependencies)
  list(REMOVE_ITEM dependencies ${module})

  set(${deps} ${dependencies})
endmacro()

macro(vscge_separate_dependencies _h_deps _cc_deps pub_deps iface_deps pvt_deps)
  # Gets lists from names
  set(h_deps ${${_h_deps}})
  set(cc_deps ${${_cc_deps}})
  vscge_debug("DEPS::${module}_h_deps::      ${h_deps}")
  vscge_debug("DEPS::${module}_cc_deps::     ${cc_deps}")

  # Union
  list(APPEND union ${h_deps} ${cc_deps})
  if(union)
    list(REMOVE_DUPLICATES union)
  endif()
  vscge_debug("DEPS::${module}_union_deps::  ${union}")

  # Left Diff
  list(APPEND left ${h_deps})
  if(cc_deps)
    list(REMOVE_ITEM left ${cc_deps})
  endif()
  vscge_debug("DEPS::${module}_left_deps::   ${left}")

  # Right Diff
  list(APPEND right ${cc_deps})
  if(h_deps)
    list(REMOVE_ITEM right ${h_deps})
  endif()
  vscge_debug("DEPS::${module}_right_deps::  ${right}")

  # Symm Diff
  list(APPEND symm ${left} ${right})
  if(symm)
    list(REMOVE_DUPLICATES symm)
  endif()
  vscge_debug("DEPS::${module}_symm_deps::   ${symm}")

  # Public Deps will be h_deps intersected with cc_deps == union minus symm
  list(APPEND inter ${union})
  if(symm)
    list(REMOVE_ITEM inter ${symm})
  endif()
  set(${pub_deps} ${inter})

  # Interface Deps is h_deps minus cc_deps == left
  set(${iface_deps} ${left})

  # Private Deps is cc_deps minus h_deps == right
  set(${pvt_deps} ${right})
endmacro()

macro(vscge_module_common)
  include("${VSCGE_SOURCE_ROOT}/cmake/VSCGEModuleCommon.cmake")
endmacro()

macro(vscge_add_module_test module test_folder)
  if(BUILD_VSCGE_TESTS)
    vscge_check("Configuring tests")
    add_subdirectory(${test_folder} ${VSCGE_ROOT}/tmp/test/${module})
    vscge_pass()
  endif()
endmacro()
