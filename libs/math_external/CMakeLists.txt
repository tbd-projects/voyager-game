cmake_minimum_required(VERSION 3.0.0)

set(PROJECT_NAME math_external_lib)
set(LIBRARY_NAME math_external_lib)

connect_lib(${LIBRARY_NAME} ${PROJECT_NAME} math_imported)

add_subdirectory(test)