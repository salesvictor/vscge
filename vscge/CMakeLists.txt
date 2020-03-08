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

message(STATUS "Configuring VSCGE version: ${VSCGE_VERSION}")

set(
  VSCGE_SOURCE
  src/core/application.cc
  src/core/renderer.cc
  src/core/timer.cc
  src/debug/debug.cc
  src/logger/logger.cc
  src/logger/tee.cc
  src/profiler/profiler.cc
  src/utils/conversions.cc
  include/vscge/logger/logger.h
  include/vscge/version.h
  include/vscge/vscge.h
  include/vscge/core/application.h
  include/vscge/core/core.h
  include/vscge/core/renderer.h
  include/vscge/core/timer.h
  include/vscge/debug/debug.h
  include/vscge/event/event.h
  include/vscge/event/key_event.h
  include/vscge/event/mouse_event.h
  include/vscge/logger/logger.h
  include/vscge/logger/tee.h
  include/vscge/profiler/profiler.h
  include/vscge/utils/conversions.h
)

add_library(
  vscge STATIC
  ${VSCGE_SOURCE}
)

find_program(
  CLANG_TIDY_EXE
  NAMES "clang-tidy"
  DOC "Path to clang-tidy"
)
if(NOT CLANG_TIDY_EXE)
  message(STATUS "clang-tidy not found")
else()
  message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
  set(CLANG_TIDY_CHECKS "-*")
  string(
    APPEND CLANG_TIDY_CHECKS
    ",google-*"
    ",modernize-*,-modernize-use-trailing-return-type"
    ",clang-analyzer-*,-clang-diagnostic-address-of-temporary"
    ",cppcoreguidelines-*,-cppcoreguidelines-pro-type-union-access"
  )
  set(DO_CLANG_TIDY "${CLANG_TIDY_EXE}" "-checks=${CLANG_TIDY_CHECKS} -header-filter=.*")
endif()

set_target_properties(
  vscge PROPERTIES
  VERSION ${PROJECT_VERSION}
  ARCHIVE_OUTPUT_DIRECTORY ${VSCGE_ROOT}/lib
  LIBRARY_OUTPUT_DIRECTORY ${VSCGE_ROOT}/lib
  RUNTIME_OUTPUT_DIRECTORY ${VSCGE_ROOT}/lib
)
find_program(
  CPPLINT_EXE
  NAMES "cpplint"
  DOC "Path to cpplint"
)
if(NOT CPPLINT_EXE)
  message(STATUS "cpplint not found")
else()
  message(STATUS "cpplint found: ${CPPLINT_EXE}")
  message(STATUS "configuring cpplint")
  set(VSCGE_LINT_FILES "")
  foreach(file ${VSCGE_SOURCE})
    list(APPEND VSCGE_LINT_FILES "vscge/${file}")
  endforeach()
  set(CPPLINT_FILTERS "-build/c++11")
  add_custom_target(
    lint
    ALL
    COMMAND ${CPPLINT_EXE} "--filter=${CPPLINT_FILTERS}" ${VSCGE_LINT_FILES}
    DEPENDS ${VSCGE_SOURCE}
    WORKING_DIRECTORY "${VSCGE_SOURCE_ROOT}"
    COMMENT "Linting project"
    VERBATIM
  )
  message(STATUS "configuring cpplint - done")
endif()
find_program(
  CPPCHECK_EXE
  NAMES "cppcheck"
)
set_target_properties(
  vscge PROPERTIES
  CXX_CLANG_TIDY "${DO_CLANG_TIDY}"
# CXX_CPPCHECK "${CPPCHECK_EXE}"
)
target_include_directories(
  vscge
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PUBLIC $<INSTALL_INTERFACE:include>
  PRIVATE src
)

set(VSCGE_COMPILER "${CMAKE_CXX_COMPILER_ID}")

message(STATUS "Configuring ${VSCGE_COMPILER} compiler")
target_compile_features(vscge PRIVATE cxx_std_20)

target_compile_definitions(vscge PUBLIC VS_PROFILE)

if(VSCGE_COMPILER STREQUAL "GNU")
  set(COMPILE_PRIVATE_FLAGS -Wall -Wextra)
  set(COMPILE_DEBUG_FLAGS -g)
  set(COMPILE_RELEASE_FLAGS -O2)
elseif(VSCGE_COMPILER STREQUAL "MSVC")
  set(COMPILE_PRIVATE_FLAGS /std:c++latest)
  set(COMPILE_DEBUG_FLAGS /std:c++latest)
  set(COMPILE_RELEASE_FLAGS /std:c++latest)
endif()

target_compile_options(
  vscge
  PRIVATE ${COMPILE_PRIVATE_FLAGS}
  PUBLIC $<$<CONFIG:DEBUG>: ${COMPILE_DEBUG_FLAGS}>
  PUBLIC $<$<CONFIG:RELEASE>: ${COMPILE_RELEASE_FLAGS}>
)
message(STATUS "Configuring ${VSCGE_COMPILER} compiler - done")

add_library(vs::cge ALIAS vscge)

if(BUILD_VSCGE_TESTS)
  message(STATUS "Configuring VSCGE unit tests")
  add_subdirectory(test ${VSCGE_ROOT}/test)
  message(STATUS "Configuring VSCGE unit tests - done")
endif()

if(BUILD_VSCGE_EXAMPLES)
  message(STATUS "Configuring VSCGE examples")
  add_subdirectory(example ${VSCGE_ROOT}/example)
  message(STATUS "Configuring VSCGE examples - done")
endif()

message(STATUS "Configuring VSCGE version: ${VSCGE_VERSION} - done")

add_executable(Logger src/logger/logger_entry_point.cc)
target_link_libraries(Logger vs::cge)
target_compile_features(Logger PRIVATE cxx_std_17)