target_sources(
  ${module}
  ${INTERFACE_OR_PUBLIC}
    include/vscge/${module}/base_event.h
    include/vscge/${module}/event.h
    include/vscge/${module}/key_event.h
    include/vscge/${module}/mouse_event.h
)

# vscge_target_sources_platform(
#   event
#   key_event.cc
# )

target_link_libraries(
  ${module}
  ${INTERFACE_OR_PUBLIC}
    vs::memory
)
