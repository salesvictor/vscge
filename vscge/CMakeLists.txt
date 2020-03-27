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

vscge_check("Configuring VSCGE version: ${VSCGE_VERSION}")

# TODO(Victor): Change this to a module-driven approach ala OpenCV.
set(
  VSCGE_SOURCE
  src/core/application.cc
  # src/core/renderer.cc
  src/core/timer.cc
  src/debug/debug.cc
  src/instrumentation/profiler.cc
  src/logger/logger.cc
  src/logger/tee.cc
  # src/utils/conversions.cc
  include/vscge/logger/logger.h
  include/vscge/version.h
  include/vscge/vscge.h
  include/vscge/core/application.h
  include/vscge/core/core.h
  # include/vscge/core/renderer.h
  include/vscge/core/timer.h
  include/vscge/debug/debug.h
  include/vscge/event/event.h
  include/vscge/event/key_event.h
  include/vscge/event/mouse_event.h
  include/vscge/instrumentation/memory.h
  include/vscge/instrumentation/profiler.h
  include/vscge/logger/logger.h
  include/vscge/logger/tee.h
  # include/vscge/utils/conversions.h
)

add_library(
  vscge
  ${VSCGE_SOURCE}
)

find_package(Python3 COMPONENTS Interpreter)
add_custom_target(
  swizzle_generator
  COMMAND ${Python3_EXECUTABLE} ${VSCGE_SOURCE_ROOT}/tool/swizzle_include_generator.py 1 > ${VSCGE_SOURCE_ROOT}/vscge/include/vscge/math/detail/swizzle_vec1.inc
  COMMAND ${Python3_EXECUTABLE} ${VSCGE_SOURCE_ROOT}/tool/swizzle_include_generator.py 2 > ${VSCGE_SOURCE_ROOT}/vscge/include/vscge/math/detail/swizzle_vec2.inc
  COMMAND ${Python3_EXECUTABLE} ${VSCGE_SOURCE_ROOT}/tool/swizzle_include_generator.py 3 > ${VSCGE_SOURCE_ROOT}/vscge/include/vscge/math/detail/swizzle_vec3.inc
  COMMAND ${Python3_EXECUTABLE} ${VSCGE_SOURCE_ROOT}/tool/swizzle_include_generator.py 4 > ${VSCGE_SOURCE_ROOT}/vscge/include/vscge/math/detail/swizzle_vec4.inc
  COMMENT "Building swizzles"
  VERBATIM
)

add_dependencies(vscge swizzle_generator)

# ==============================================================================
# Static checking
# ==============================================================================
# TODO(Victor): Find a better way to handle static checkers, maybe on a .cmake?
vscge_check("Finding static checkers")

vscge_check("Finding clang-tidy")
find_program(
  CLANG_TIDY_EXE
  NAMES "clang-tidy"
  DOC "Path to clang-tidy"
)
if(NOT CLANG_TIDY_EXE)
  vscge_fail("not found")
else()
  vscge_pass("found: ${CLANG_TIDY_EXE}")
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

vscge_check("Finding cpplint")
find_program(
  CPPLINT_EXE
  NAMES "cpplint"
  DOC "Path to cpplint"
)
if(NOT CPPLINT_EXE)
  vscge_fail("not found")
else()
  vscge_pass("found: ${CPPLINT_EXE}")
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

vscge_check("Finding cppcheck")
find_program(
  CPPCHECK_EXE
  NAMES "cppcheck"
)
if(NOT CPPCHECK_EXE)
  vscge_fail("not found")
else()
  vscge_pass("found: ${CPPCHECK_EXE}")
  # set_target_properties(
  #   vscge PROPERTIES
  #   CXX_CPPCHECK "${CPPCHECK_EXE}"
  # )
endif()

vscge_check("Finding iwyu")
find_program(
  IWYU_EXE
  NAMES "include-what-you-use"
)
if(NOT IWYU_EXE)
  vscge_fail("not found")
else()
  vscge_pass("found: ${IWYU_EXE}")
  set_target_properties(
    vscge PROPERTIES
    CXX_INCLUDE_WHAT_YOU_USE "${IWYU_EXE}"
  )
endif()

vscge_pass("done")
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
set(VSCGE_COMPILER_VERSION "${CMAKE_CXX_COMPILER_VERSION}")
set(VSCGE_SIMULATED_COMPILER "${CMAKE_CXX_SIMULATE_ID}")
vscge_check("Configuring ${VSCGE_COMPILER} ${VSCGE_COMPILER_VERSION} compiler")

if(NOT VSCGE_SIMULATED_COMPILER STREQUAL "")
  message(STATUS "Simulating compiler ${VSCGE_SIMULATED_COMPILER}")
endif()

# TODO(Victor): Check for C++20 compatibility, so that we can use
# [[no_unique_address]] attribute for swizzles.
target_compile_features(vscge PUBLIC cxx_std_17)

if(VSCGE_COMPILER STREQUAL "Clang")
  set(COMPILE_PRIVATE_FLAGS /W4 /WX)

  set(COMPILE_RELEASE_FLAGS -O2)
elseif(VSCGE_COMPILER STREQUAL "GNU")
  set(COMPILE_PRIVATE_FLAGS -Wall -Wextra)
  set(COMPILE_DEBUG_FLAGS -g)
  set(COMPILE_RELEASE_FLAGS -O2)
elseif(VSCGE_COMPILER STREQUAL "MSVC")

  set(COMPILE_PRIVATE_FLAGS /MP /Wall /WX /std:c++latest)

  # Disables anoying warnings.
  list(APPEND COMPILE_PRIVATE_FLAGS /wd4514 /wd4710 /wd4820 /wd4668 /wd5039)

  # default/copy/move assignment/constructors implicitly deleted.
  list(APPEND COMPILE_PRIVATE_FLAGS /wd4625 /wd4626 /wd5026 /wd5027 /wd4623)

  # Spectre something.
  list(APPEND COMPILE_PRIVATE_FLAGS /wd5045)

  # conversions that make inter API a pain.
  list(APPEND COMPILE_PRIVATE_FLAGS /wd4267 /wd4365)

  set(COMPILE_DEBUG_FLAGS)
  set(COMPILE_RELEASE_FLAGS)
endif()

target_compile_options(
  vscge
  PRIVATE ${COMPILE_PRIVATE_FLAGS}
  PUBLIC $<$<CONFIG:DEBUG>: ${COMPILE_DEBUG_FLAGS}>
  PUBLIC $<$<CONFIG:RELEASE>: ${COMPILE_RELEASE_FLAGS}>
)

vscge_pass()
# ==============================================================================


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
#]]
if(BUILD_VSCGE_TESTS)
  vscge_check("Configuring VSCGE tests")
  add_subdirectory(test ${VSCGE_ROOT}/test)
  vscge_pass()
endif()
# ==============================================================================

add_library(vs::cge ALIAS vscge)
vscge_pass()

add_executable(test WIN32 src/platform/windows/entry_point.cc)
