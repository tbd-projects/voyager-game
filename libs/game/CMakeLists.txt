cmake_minimum_required(VERSION 3.0.0)

set(PROJECT_NAME game_lib)
set(LIBRARY_NAME game_lib)

connect_lib(${LIBRARY_NAME} ${PROJECT_NAME} game)

if (NOT (TARGET debug_lib))
    message(FATAL_ERROR "debug_lib targets NOT found")
endif()


if (NOT (TARGET loaders_lib))
    message(FATAL_ERROR "loaders_lib targets NOT found")
endif()

if (NOT (TARGET physics_lib))
    message(FATAL_ERROR "physics_lib targets NOT found")
endif()
target_link_libraries(${LIBRARY_NAME} debug_lib)
target_link_libraries(${LIBRARY_NAME} physics_lib)
target_link_libraries(${LIBRARY_NAME} loaders_lib)

add_subdirectory(test)
