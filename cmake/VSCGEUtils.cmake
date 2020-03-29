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

macro(vscge_debug)
  if(VS_DEVELOPER_MODE)
    list(APPEND CMAKE_MESSAGE_CONTEXT "debug")
    message(STATUS "${ARGN}")
    list(POP_BACK CMAKE_MESSAGE_CONTEXT)
  endif()
endmacro()

macro(vscge_check message)
  message(CHECK_START ${message})
  list(APPEND CMAKE_MESSAGE_INDENT "  ")
endmacro()

macro(vscge_pass)
  list(POP_BACK CMAKE_MESSAGE_INDENT)
  if(NOT ${ARGC} EQUAL 0)
    message(CHECK_PASS ${ARGN})
  else()
    message(CHECK_PASS "done")
  endif()
endmacro()

macro(vscge_fail)
  list(POP_BACK CMAKE_MESSAGE_INDENT)
  if(NOT ${ARGC} EQUAL 0)
    message(CHECK_FAIL ${ARGN})
  else()
    message(CHECK_FAIL "failed")
  endif()
endmacro()

function(vscge_option option description default)
  set(${option} ${default} CACHE STRING ${description})

  set(POSSIBLE_VALUES ${default})
  if(${default} STREQUAL "ON")
    list(APPEND POSSIBLE_VALUES OFF)
  elseif(${default} STREQUAL "OFF")
    list(APPEND POSSIBLE_VALUES ON)
  elseif(NOT ${ARGC} EQUAL 0)
    list(APPEND POSSIBLE_VALUES ${ARGN})
  endif()

  list(SORT POSSIBLE_VALUES)

  set_property(CACHE ${option} PROPERTY STRINGS ${POSSIBLE_VALUES})

  vscge_debug("${option}|${description}|${default}|${POSSIBLE_VALUES}|${${option}}")
endfunction()
