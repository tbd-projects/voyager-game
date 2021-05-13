cmake_minimum_required(VERSION 3.1x)

set(PROJECT_NAME game_lib)
set(LIBRARY_NAME game_lib)

connect_lib(${LIBRARY_NAME} ${PROJECT_NAME} game)

add_subdirectory(test)
