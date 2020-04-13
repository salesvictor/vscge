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

macro(vscge_debug)
  if(VS_DEVELOPER_MODE)
    list(APPEND CMAKE_MESSAGE_CONTEXT "debug")
    message(STATUS "${ARGN}")
    list(POP_BACK CMAKE_MESSAGE_CONTEXT)
  endif()
endmacro()

macro(vscge_check message)
  message(CHECK_START ${message})
  list(APPEND CMAKE_MESSAGE_INDENT "  ")
endmacro()

macro(vscge_pass)
  list(POP_BACK CMAKE_MESSAGE_INDENT)
  if(NOT ${ARGC} EQUAL 0)
    message(CHECK_PASS ${ARGN})
  else()
    message(CHECK_PASS "done")
  endif()
endmacro()

macro(vscge_fail)
  list(POP_BACK CMAKE_MESSAGE_INDENT)
  if(NOT ${ARGC} EQUAL 0)
    message(CHECK_FAIL ${ARGN})
  else()
    message(CHECK_FAIL "failed")
  endif()
endmacro()

function(vscge_option option description default)
  set(${option} ${default} CACHE STRING ${description})

  set(POSSIBLE_VALUES ${default})
  if(${default} STREQUAL "ON")
    list(APPEND POSSIBLE_VALUES OFF)
  elseif(${default} STREQUAL "OFF")
    list(APPEND POSSIBLE_VALUES ON)
  elseif(NOT ${ARGC} EQUAL 0)
    list(APPEND POSSIBLE_VALUES ${ARGN})
  endif()

  list(SORT POSSIBLE_VALUES)

  set_property(CACHE ${option} PROPERTY STRINGS ${POSSIBLE_VALUES})

  vscge_debug("${option}|${description}|${default}|${POSSIBLE_VALUES}|${${option}}")
endfunction()

macro(vscge_add_analyzers module)
  vscge_debug("Adding analyzers to ${module}")
  if(CLANG_TIDY_EXE)
    vscge_debug("Adding clang-tidy")
    set_target_properties(
      ${module} PROPERTIES
      CXX_CLANG_TIDY ${CLANG_TIDY_EXE}
    )
  endif()

  if(CPPCHECK_EXE)
    set_target_properties(
      ${module} PROPERTIES
      CXX_CPPCHECK ${CPPCHECK_EXE}
    )
  endif()

  if(IWYU_EXE)
    vscge_debug("Adding iwyu")
    set_target_properties(
      ${module} PROPERTIES
      CXX_IWYU ${IWYU_EXE}
    )
  endif()
endmacro()

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
  add_subdirectory(${module})
  add_library(vs::${module} ALIAS ${module})
  target_link_libraries(vscge INTERFACE vs::${module})
  vscge_pass()
endmacro()

macro(vscge_target_sources_platform target)
  if(VS_TARGET_PLATFORM STREQUAL "Windows")
    set(PLATFORM_PREFIX src/platform/windows)
  elseif(VS_TARGET_PLATFORM STREQUAL "Windows Console")
    set(PLATFORM_PREFIX src/platform/windows_console)
  endif()

  foreach(SOURCE_FILE ${ARGN})
    target_sources(
      ${target}
      PRIVATE
        ${PLATFORM_PREFIX}/${SOURCE_FILE}
    )
  endforeach()
endmacro()

macro(vscge_add_module_test module test_folder)
  if(BUILD_VSCGE_TESTS)
    vscge_check("Configuring tests")
    add_subdirectory(${test_folder} test/${module})
    vscge_pass()
  endif()
endmacro()
