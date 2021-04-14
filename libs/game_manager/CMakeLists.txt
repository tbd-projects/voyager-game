cmake_minimum_required(VERSION 3.1x)

set(PROJECT_NAME game_manager_lib)
set(LIBRARY_NAME game_manager_lib)

connect_lib(${LIBRARY_NAME} ${PROJECT_NAME} game_manager)

add_subdirectory(test)