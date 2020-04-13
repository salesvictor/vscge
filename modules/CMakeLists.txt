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
add_library(vscge INTERFACE)

if(VS_DEVELOPER_MODE)
  include(${VSCGE_SOURCE_ROOT}/cmake/VSCGEStaticAnalyzers.cmake)
endif()

vscge_add_module(core)
vscge_add_module(debug)
vscge_add_module(event)
vscge_add_module(instrumentation)
vscge_add_module(logger)
vscge_add_module(math)
vscge_add_module(memory)
vscge_add_module(util)

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

target_compile_features(vscge INTERFACE cxx_std_17)

if(VSCGE_COMPILER STREQUAL "Clang")
  set(COMPILE_PRIVATE_FLAGS /W4 /WX)

  set(COMPILE_RELEASE_FLAGS -O2)
elseif(VSCGE_COMPILER STREQUAL "GNU")
  set(COMPILE_PRIVATE_FLAGS -Wall -Wextra)
  set(COMPILE_DEBUG_FLAGS -g)
  set(COMPILE_RELEASE_FLAGS -O2)
elseif(VSCGE_COMPILER STREQUAL "MSVC")

  set(COMPILE_PRIVATE_FLAGS /MP /Wall /WX)

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

# target_compile_options(
  # vscge
  # PRIVATE ${COMPILE_PRIVATE_FLAGS}
  # PUBLIC $<$<CONFIG:DEBUG>: ${COMPILE_DEBUG_FLAGS}>
  # PUBLIC $<$<CONFIG:RELEASE>: ${COMPILE_RELEASE_FLAGS}>
# )

vscge_pass()
# ==============================================================================
# Options handling
# ==============================================================================
# TODO(Victor): Make a macro to handle options?
#[[
if(BUILD_SHARED_LIBS)
  target_compile_definitions(vscge PUBLIC VS_DLL)
  target_compile_definitions(vscge PRIVATE VS_DLL_EXPORTS)
endif()
#]]
# ==============================================================================

add_library(vs::cge ALIAS vscge)
vscge_pass()
