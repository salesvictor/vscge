message(STATUS "Configuring VSCGE version: ${VSCGE_VERSION}")

add_library(
  vscge
  src/application.cc
  src/core/timer.cc
  src/utils/conversions.cc
)

set_target_properties(
  vscge PROPERTIES
  VERSION ${PROJECT_VERSION}
  ARCHIVE_OUTPUT_DIRECTORY ${VSCGE_ROOT}/lib
  LIBRARY_OUTPUT_DIRECTORY ${VSCGE_ROOT}/lib
)
target_include_directories(
  vscge
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PUBLIC $<INSTALL_INTERFACE:include>
  PRIVATE src
)

set(VSCGE_COMPILER "${CMAKE_CXX_COMPILER_ID}")

message(STATUS "Configuring ${VSCGE_COMPILER} compiler flags")
if(VSCGE_COMPILER STREQUAL "GNU")
  set(COMPILE_DEBUG_FLAGS -g)
  set(COMPILE_RELEASE_FLAGS -O2)
  set(COMPILE_PRIVATE_FLAGS -Wall -Wextra)
elseif(VSCGE_COMPILER STREQUAL "MSVC")
  set(COMPILE_DEBUG_FLAGS /D_UNICODE /DUNICODE /std:c++latest)
  set(COMPILE_RELEASE_FLAGS /D_UNICODE /DUNICODE /std:c++latest)
  set(COMPILE_PRIVATE_FLAGS /D_UNICODE /DUNICODE /std:c++latest)
endif()

target_compile_options(
  vscge
  PRIVATE ${COMPILE_PRIVATE_FLAGS}
  PUBLIC $<$<CONFIG:DEBUG>: ${COMPILE_DEBUG_FLAGS}>
  PUBLIC $<$<CONFIG:RELEASE>: ${COMPILE_RELEASE_FLAGS}>
)
message(STATUS "Configuring ${VSCGE_COMPILER} compiler flags - done")

add_library(vs::cge ALIAS vscge)

if(BUILD_VSCGE_TESTS)
  message(STATUS "Configuring VSCGE unit tests")
  add_subdirectory(test ${VSCGE_ROOT}/test)
  message(STATUS "Configuring VSCGE unit tests - done")
endif()

if(BUILD_VSCGE_EXAMPLES)
  message(STATUS "Configuring VSCGE examples")
  add_subdirectory(example ${VSCGE_ROOT}/example)
  message(STATUS "Configuring VSCGE examples - done")
endif()

message(STATUS "Configuring VSCGE version: ${VSCGE_VERSION} - done")