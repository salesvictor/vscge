target_sources(
  logger
  INTERFACE
    include/vscge/logger/logger.h
  PUBLIC
    include/vscge/logger/tee.h
  PRIVATE
    src/tee.cc
)

vscge_target_sources_platform(
  logger
  logger.cc
)

if(VS_ENABLE_LOGGER)
  add_executable(Logger src/logger_entry_point.cc)
  target_link_libraries(Logger vscge)
  target_compile_features(Logger PRIVATE cxx_std_17)
endif()

target_link_libraries(
  logger
  PRIVATE
    vs::instrumentation
)
