target_sources(
  math
  INTERFACE
    include/vscge/math/matrix.h
    include/vscge/math/vector.h
    include/vscge/math/detail/swizzle.h
)

find_package(Python3 COMPONENTS Interpreter)
add_custom_target(
  swizzle_generator
  COMMAND ${Python3_EXECUTABLE} ${VSCGE_SOURCE_ROOT}/tool/swizzle_include_generator.py 1 > ${CMAKE_CURRENT_SOURCE_DIR}/include/vscge/math/detail/swizzle_vec1.inc
  COMMAND ${Python3_EXECUTABLE} ${VSCGE_SOURCE_ROOT}/tool/swizzle_include_generator.py 2 > ${CMAKE_CURRENT_SOURCE_DIR}/include/vscge/math/detail/swizzle_vec2.inc
  COMMAND ${Python3_EXECUTABLE} ${VSCGE_SOURCE_ROOT}/tool/swizzle_include_generator.py 3 > ${CMAKE_CURRENT_SOURCE_DIR}/include/vscge/math/detail/swizzle_vec3.inc
  COMMAND ${Python3_EXECUTABLE} ${VSCGE_SOURCE_ROOT}/tool/swizzle_include_generator.py 4 > ${CMAKE_CURRENT_SOURCE_DIR}/include/vscge/math/detail/swizzle_vec4.inc
  COMMENT "Building swizzles"
  VERBATIM
)

add_dependencies(math swizzle_generator)
