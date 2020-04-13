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

vscge_check("Finding static analyzers")

vscge_check("Finding clang-tidy")
find_program(
  CLANG_TIDY_EXE
  NAMES "clang-tidy"
)
if(NOT CLANG_TIDY_EXE)
  vscge_fail("not found")
else()
  vscge_pass("found: ${CLANG_TIDY_EXE}")
endif()

#[[
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
#]]

vscge_check("Finding cppcheck")
find_program(
  CPPCHECK_EXE
  NAMES "cppcheck"
)
if(NOT CPPCHECK_EXE)
  vscge_fail("not found")
else()
  vscge_pass("found: ${CPPCHECK_EXE}")
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
endif()

vscge_pass("done")
