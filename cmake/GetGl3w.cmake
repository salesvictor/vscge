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

include(FetchContent)

set(FETCHCONTENT_BASE_DIR ${VSCGE_ROOT}/tmp/external)

FetchContent_Declare(
  gl3w_lib
  GIT_REPOSITORY https://github.com/skaslev/gl3w.git
)

FetchContent_GetProperties(gl3w_lib)

if(NOT gl3w_lib_POPULATED)
  message(STATUS "Populating gl3w")
  FetchContent_Populate(googletest)
  message(STATUS "Populating gl3w - done")
  add_subdirectory(${gl3w_SOURCE_DIR} ${gl3w_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()