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

cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

set(VSCGE_ROOT ${CMAKE_CURRENT_BINARY_DIR})
set(VSCGE_SOURCE_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

include(cmake/VSCGEVersion.cmake)
include(cmake/VSCGEUtils.cmake)

project(
  VSCGE
  VERSION ${VSCGE_VERSION}
  DESCRIPTION "VS Component Game Engine"
  LANGUAGES CXX
)

# ==============================================================================
# Options
# ==============================================================================
set(CMAKE_MESSAGE_CONTEXT_SHOW TRUE)

vscge_option(BUILD_SHARED_LIBS    "Build using shared libraries" OFF)
vscge_option(BUILD_VSCGE_TESTS    "Build VSCGE tests"            ON)
vscge_option(BUILD_VSCGE_EXAMPLES "Build VSCGE examples"         OFF)

vscge_option(VS_ENABLE_ASSERTS  "Enable VS_ASSERT* macros" ON)
vscge_option(VS_ENABLE_PROFILER "Enable profiler"          ON)
vscge_option(VS_ENABLE_LOGGER   "Enable logger"            ON)

vscge_option(VS_TARGET_PLATFORM "End-user platform" "Windows" "Windows Console")

# TODO(Victor): Turn this off on prod
vscge_option(VS_DEVELOPER_MODE "Engine Developer" ON)
# ==============================================================================

add_subdirectory(modules)

if(BUILD_VSCGE_EXAMPLES)
  vscge_check("Configuring VSCGE examples")
  add_subdirectory(examples tmp)
  vscge_pass()
endif()

find_package(Doxygen OPTIONAL_COMPONENTS dot)
if(Doxygen_FOUND)
  add_custom_target(
      graphviz ALL
      COMMAND ${CMAKE_COMMAND} "--graphviz=graphviz/vscge.dot" .
      COMMAND ${DOXYGEN_DOT_EXECUTABLE} -Tpng graphviz/vscge.dot -o graphviz/vscge.png
      WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
  )
endif()
