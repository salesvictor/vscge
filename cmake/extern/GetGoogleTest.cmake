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

# NOTE: Remember to `enable_testing()` on a proper root directory!

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

include(FetchContent)

if(DEFINED "${PROJECT_NAME}_FETCHCONTENT_BASE_DIR")
  set(FETCHCONTENT_BASE_DIR ${${PROJECT_NAME}_FETCHCONTENT_BASE_DIR})
endif()

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.8.1
)

FetchContent_GetProperties(googletest)

if(NOT googletest_POPULATED)
  message(STATUS "Populating googletest")
  FetchContent_Populate(googletest)
  message(STATUS "Populating googletest - done")
  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

include(GoogleTest)
enable_testing()

macro(add_gtest TEST_NAME)
  add_executable(${TEST_NAME} ${TEST_NAME}.cc)
  target_link_libraries(${TEST_NAME} PRIVATE gtest gtest_main gmock ${ARGN})
  gtest_discover_tests(
    ${TEST_NAME}
    EXTRA_ARGS --gtest_color=yes
    TEST_PREFIX "${TEST_NAME}."
    PROPERTIES FOLDER "test"
  )
endmacro()

add_custom_target(
  check
  COMMAND ${CMAKE_CTEST_COMMAND} --force-new-ctest-process --output-on-failure
)
