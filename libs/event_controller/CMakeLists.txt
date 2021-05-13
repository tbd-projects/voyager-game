cmake_minimum_required(VERSION 3.1x)

set(PROJECT_NAME event_controller_lib)
set(LIBRARY_NAME event_controller_lib)

connect_lib(${LIBRARY_NAME} ${PROJECT_NAME} event_controller)

add_subdirectory(test)