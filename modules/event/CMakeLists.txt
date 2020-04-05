target_sources(
  event
  INTERFACE
    include/vscge/event/base_event.h
    include/vscge/event/event.h
    include/vscge/event/key_event.h
    include/vscge/event/mouse_event.h
)

vscge_target_sources_platform(
  event
  key_event.cc
)

target_link_libraries(
  event
  PUBLIC
    vs::memory
)
