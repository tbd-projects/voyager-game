cmake_minimum_required(VERSION 3.0.0)

set(PROJECT_NAME menu_lib)
set(LIBRARY_NAME menu_lib)

connect_lib(${LIBRARY_NAME} ${PROJECT_NAME} menu)

target_link_libraries(${LIBRARY_NAME} graphics_lib)

#add_subdirectory(test)