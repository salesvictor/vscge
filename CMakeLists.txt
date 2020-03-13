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

cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

set(VSCGE_ROOT ${CMAKE_CURRENT_BINARY_DIR})
set(VSCGE_SOURCE_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

include(cmake/VSCGEVersion.cmake)

project(
  VSCGE
  VERSION ${VSCGE_VERSION}
  DESCRIPTION "VS Component Game Engine"
  LANGUAGES CXX
)

# Options
# ==============================================================================
option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)
option(BUILD_VSCGE_TESTS "Build VSCGE tests" OFF)
option(BUILD_VSCGE_EXAMPLES "Build VSCGE examples" ON)

option(VS_ENABLE_ASSERTS "Enable VS_ASSERT* macros" ON)
option(VS_ENABLE_PROFILER "Enable profiler" ON)
option(VS_ENABLE_LOGGER "Enable logger" ON)
# ==============================================================================

add_subdirectory(vscge)

if(BUILD_VSCGE_EXAMPLES)
  message(STATUS "Configuring VSCGE examples")
  add_subdirectory(examples tmp)
  message(STATUS "Configuring VSCGE examples - done")
endif()
