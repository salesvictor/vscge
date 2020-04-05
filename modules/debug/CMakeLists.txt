target_sources(
  debug
  INTERFACE
    include/vscge/debug/debug.h
  PRIVATE
    src/debug.cc
)

target_link_libraries(
  debug
  PRIVATE
    vs::logger
)
