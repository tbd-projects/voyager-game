cmake_minimum_required(VERSION 3.1x)

set(PROJECT_NAME debug_lib)
set(LIBRARY_NAME debug_lib)

connect_lib(${LIBRARY_NAME} ${PROJECT_NAME} debug)

add_subdirectory(test)