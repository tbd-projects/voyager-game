cmake_minimum_required(VERSION 3.1x)

set(PROJECT_NAME shop_lib)
set(LIBRARY_NAME shop_lib)

connect_lib(${LIBRARY_NAME} ${PROJECT_NAME} shop)

add_subdirectory(test)