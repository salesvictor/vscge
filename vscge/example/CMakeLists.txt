add_executable(Maze maze.cc)
target_link_libraries(Maze vs::cge)

add_executable(GameOfLife game_of_life.cc)
target_link_libraries(GameOfLife vs::cge)