add_executable(Maze maze.cc)
target_link_libraries(Maze vs::cge)

add_executable(GameOfLife game_of_life.cc)
target_link_libraries(GameOfLife vs::cge)

add_custom_command(
  TARGET GameOfLife POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
  $<TARGET_FILE:vs::cge> $<TARGET_FILE_DIR:GameOfLife>
)