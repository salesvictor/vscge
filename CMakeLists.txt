cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

set(VSCGE_ROOT ${CMAKE_CURRENT_BINARY_DIR})
set(VSCGE_SOURCE_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

include(cmake/VSCGEVersion.cmake)

message(STATUS "Configuring VSCGE version: ${VSCGE_VERSION}")

project(
  vscge
  VERSION ${VSCGE_VERSION}
  DESCRIPTION "VS Console Game Engine"
  LANGUAGES CXX
)

option(BUILD_VSCGE_TESTS "Build VSCGE tests" OFF)
option(BUILD_VSCGE_EXAMPLES "Build VSCGE examples" ON)

add_subdirectory(vscge tmp)