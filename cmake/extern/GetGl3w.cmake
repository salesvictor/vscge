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

# Install gl3w before this
find_package(gl3w REQUIRED)

# This should be called at an appropriate root dir, but if it isn't, uncomment
# the following line
#set_target_properties(gl3w PROPERTIES IMPORTED_GLOBAL TRUE)

# gl3w is currently not functioning properly, so you have to run the python
# script before adding the directory, see https://github.com/skaslev/gl3w/issues/66.
#
# The original CMakeLists.txt file was changed to make everything work.
#
# add_subdirectory also didn't work
#[[
add_subdirectory(gl3w EXCLUDE_FROM_ALL)
#]]

# FetchContent currently not working, raised the issue at
# https://github.com/skaslev/gl3w/issues/66
#[[
include(FetchContent)

FetchContent_Declare(
  gl3w_lib
  GIT_REPOSITORY https://github.com/skaslev/gl3w.git
)

FetchContent_GetProperties(gl3w_lib)

if(NOT gl3w_lib_POPULATED)
  message(STATUS "Populating gl3w")
  FetchContent_Populate(gl3w_lib)
  message(STATUS "Populating gl3w - done")
  add_subdirectory(${gl3w_lib_SOURCE_DIR} ${gl3w_lib_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
]]#
