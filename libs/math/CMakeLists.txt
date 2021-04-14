cmake_minimum_required(VERSION 3.0.0)

set(PROJECT_NAME math_lib)
set(LIBRARY_NAME math_lib)

connect_lib(${LIBRARY_NAME} ${PROJECT_NAME} math)

add_subdirectory(test)