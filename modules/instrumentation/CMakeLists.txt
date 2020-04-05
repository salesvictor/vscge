target_sources(
  instrumentation
  INTERFACE
    include/vscge/instrumentation/memory.h
    include/vscge/instrumentation/profiler.h
  PRIVATE
    src/profiler.cc
)
