cmake_minimum_required(VERSION 3.1x)

set(PROJECT_NAME loaders_lib)
set(LIBRARY_NAME loaders_lib)

connect_lib(${LIBRARY_NAME} ${PROJECT_NAME} loaders)

add_subdirectory(test)