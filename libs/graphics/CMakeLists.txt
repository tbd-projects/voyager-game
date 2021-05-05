cmake_minimum_required(VERSION 3.0.0)

set(PROJECT_NAME graphics_lib)
set(LIBRARY_NAME graphics_lib)

connect_lib(${LIBRARY_NAME} ${PROJECT_NAME} graphics)

add_subdirectory(test)
