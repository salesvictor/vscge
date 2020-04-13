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

set(VERSION_FILE "include/vscge/version.h")

# TODO(Victor): This check is happening at configuration time only, should
# change to be done at build time, because files can be edited and not be
# configured again.
find_package(Git)
if(Git_FOUND)
  execute_process(
    COMMAND ${GIT_EXECUTABLE} diff --name-only
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    OUTPUT_VARIABLE CHANGED_FILES
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  if(NOT CHANGED_FILES STREQUAL "")
    string(REPLACE "\n" ";" CHANGED_FILES_LIST ${CHANGED_FILES})
    list(LENGTH CHANGED_FILES_LIST CHANGE_SIZE)
    list(FIND CHANGED_FILES_LIST ${VERSION_FILE} VERSION_INDEX)
    message(DEBUG "Files changed: ${CHANGED_FILES_LIST}")

    # TODO(Victor): This fails with just one change, fix it.
    if(${CHANGE_SIZE} GREATER 0 AND ${VERSION_INDEX} EQUAL -1)
      message(
        AUTHOR_WARNING
        "Detected ${CHANGE_SIZE} file changes, but no version change, update the version!"
      )
    endif()
  endif()
endif()
file(
  STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/${VERSION_FILE}" VSCGE_VERSION_PARTS
  REGEX "#define VSCGE_VERSION_[A-Z]+[ ]+"
)

string(
  REGEX REPLACE ".+VSCGE_VERSION_MAJOR[ ]+([0-9]+).*"
  "\\1" VSCGE_VERSION_MAJOR
  "${VSCGE_VERSION_PARTS}"
)
string(
  REGEX REPLACE ".+VSCGE_VERSION_MINOR[ ]+([0-9]+).*"
  "\\1" VSCGE_VERSION_MINOR
  "${VSCGE_VERSION_PARTS}"
)
string(
  REGEX REPLACE ".+VSCGE_VERSION_PATCH[ ]+([0-9]+).*"
  "\\1" VSCGE_VERSION_PATCH
  "${VSCGE_VERSION_PARTS}"
)

set(
  VSCGE_VERSION
  "${VSCGE_VERSION_MAJOR}.${VSCGE_VERSION_MINOR}.${VSCGE_VERSION_PATCH}"
)
