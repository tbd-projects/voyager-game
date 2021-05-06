cmake_minimum_required(VERSION 3.0.0)

set(PROJECT_NAME physics_lib)
set(LIBRARY_NAME physics_lib)

connect_lib(${LIBRARY_NAME} ${PROJECT_NAME} physics)

add_subdirectory(test)