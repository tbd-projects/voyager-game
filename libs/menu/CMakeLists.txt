cmake_minimum_required(VERSION 3.1x)

set(PROJECT_NAME menu_lib)
set(LIBRARY_NAME menu_lib)

connect_lib(${LIBRARY_NAME} ${PROJECT_NAME} menu)

add_subdirectory(test)
