cmake_minimum_required(VERSION 3.1x)

set(PROJECT_NAME sf_graphics_lib)
set(LIBRARY_NAME sf_graphics_lib)

connect_lib(${LIBRARY_NAME} ${PROJECT_NAME} sf_graphics)

add_subdirectory(test)