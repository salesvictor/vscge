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

# TODO(Victor): Make a function/macro for these ".../... - done" things?
message(CHECK_START "Configuring VSCGE version: ${VSCGE_VERSION}")
list(APPEND CMAKE_MESSAGE_INDENT "  ")

# TODO(Victor): Change this to a module-driven approach ala OpenCV.
set(
  VSCGE_SOURCE
  src/core/application.cc
  src/core/renderer.cc
  src/core/timer.cc
  src/debug/debug.cc
  src/instrumentation/profiler.cc
  src/logger/logger.cc
  src/logger/tee.cc
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
  include/vscge/instrumentation/memory.h
  include/vscge/instrumentation/profiler.h
  include/vscge/logger/logger.h
  include/vscge/logger/tee.h
  include/vscge/utils/conversions.h
)

add_library(
  vscge
  ${VSCGE_SOURCE}
)

# ==============================================================================
# Static checking
# ==============================================================================
# TODO(Victor): Find a better way to handle static checkers.
message(CHECK_START "Finding static checkers")
list(APPEND CMAKE_MESSAGE_INDENT "  ")

message(CHECK_START "Finding clang-tidy")
find_program(
  CLANG_TIDY_EXE
  NAMES "clang-tidy"
  DOC "Path to clang-tidy"
)
if(NOT CLANG_TIDY_EXE)
  message(CHECK_FAIL "not found")
else()
  message(CHECK_PASS "found: ${CLANG_TIDY_EXE}")
  set(CLANG_TIDY_CHECKS "-*") # Disable everything by default.
  string(
    APPEND CLANG_TIDY_CHECKS
    ",google-*" # Use Google Style.
    ",modernize-*"
    ",-modernize-use-trailing-return-type" # Doesn't really comply with Google's Style Guide.
    ",clang-analyzer-*"
    # ",-clang-diagnostic-address-of-temporary"
    ",cppcoreguidelines-*"
    ",-cppcoreguidelines-pro-type-union-access" # We need this to get off warnings from using the Windows API.
  )
  set(DO_CLANG_TIDY "${CLANG_TIDY_EXE}" "-checks=${CLANG_TIDY_CHECKS} -header-filter=.*")
  set_target_properties(
    vscge PROPERTIES
    CXX_CLANG_TIDY "${DO_CLANG_TIDY}"
  )
endif()

message(CHECK_START "Finding cpplint")
find_program(
  CPPLINT_EXE
  NAMES "cpplint"
  DOC "Path to cpplint"
)
if(NOT CPPLINT_EXE)
  message(CHECK_FAIL "not found")
else()
  message(CHECK_PASS "found: ${CPPLINT_EXE}")
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
endif()

message(CHECK_START "Finding cppcheck")
find_program(
  CPPCHECK_EXE
  NAMES "cppcheck"
)
if(NOT CPPCHECK_EXE)
  message(CHECK_FAIL "not found")
else()
  message(CHECK_PASS "found: ${CPPCHECK_EXE}")
  # set_target_properties(
  #   vscge PROPERTIES
  #   CXX_CPPCHECK "${CPPCHECK_EXE}"
  # )
endif()

list(POP_BACK CMAKE_MESSAGE_INDENT)
message(CHECK_PASS "done")
# ==============================================================================

set_target_properties(
  vscge PROPERTIES
  VERSION ${PROJECT_VERSION}
  ARCHIVE_OUTPUT_DIRECTORY ${VSCGE_ROOT}/lib
  LIBRARY_OUTPUT_DIRECTORY ${VSCGE_ROOT}/lib
  RUNTIME_OUTPUT_DIRECTORY ${VSCGE_ROOT}/bin
)
target_include_directories(
  vscge
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PUBLIC $<INSTALL_INTERFACE:include>
  PRIVATE src
)


# ==============================================================================
# Compiler configuration.
# ==============================================================================
set(VSCGE_COMPILER "${CMAKE_CXX_COMPILER_ID}")
message(CHECK_START "Configuring ${VSCGE_COMPILER} compiler")

# TODO(Victor): Check C++20 compatibility.
target_compile_features(vscge PRIVATE cxx_std_20)


if(VSCGE_COMPILER STREQUAL "GNU")
  set(COMPILE_PRIVATE_FLAGS -Wall -Wextra)
  set(COMPILE_DEBUG_FLAGS -g)
  set(COMPILE_RELEASE_FLAGS -O2)
elseif(VSCGE_COMPILER STREQUAL "MSVC")
  set(COMPILE_PRIVATE_FLAGS /MP /Wall /WX /std:c++latest)
  set(COMPILE_DEBUG_FLAGS /std:c++latest)
  set(COMPILE_RELEASE_FLAGS /std:c++latest)
endif()

target_compile_options(
  vscge
  PRIVATE ${COMPILE_PRIVATE_FLAGS}
  PUBLIC $<$<CONFIG:DEBUG>: ${COMPILE_DEBUG_FLAGS}>
  PUBLIC $<$<CONFIG:RELEASE>: ${COMPILE_RELEASE_FLAGS}>
)
message(CHECK_PASS "done")
# ==============================================================================

add_library(vs::cge ALIAS vscge)

if(BUILD_VSCGE_TESTS)
  message(CHECK_START "Configuring VSCGE tests")
  list(APPEND CMAKE_MESSAGE_INDENT "  ")
  add_subdirectory(test ${VSCGE_ROOT}/test)
  list(POP_BACK CMAKE_MESSAGE_INDENT)
  message(CHECK_PASS "done")
endif()

list(POP_BACK CMAKE_MESSAGE_INDENT)
message(CHECK_PASS "done")

# Options handling
# ==============================================================================
# TODO(Victor): Make a macro to handle options?
if(BUILD_SHARED_LIBS)
  target_compile_definitions(vscge PUBLIC VS_DLL)
  target_compile_definitions(vscge PRIVATE VS_DLL_EXPORTS)
endif()
if(VS_ENABLE_PROFILER)
  target_compile_definitions(vscge PUBLIC VS_ENABLE_PROFILER)
endif()
if(VS_ENABLE_ASSERTS)
  target_compile_definitions(vscge PUBLIC VS_ENABLE_ASSERTS)
endif()
if(VS_ENABLE_LOGGER)
  add_executable(Logger src/logger/logger_entry_point.cc)
  target_link_libraries(Logger vs::cge)
  target_compile_features(Logger PRIVATE cxx_std_17)
endif()
# ==============================================================================
