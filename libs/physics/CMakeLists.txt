cmake_minimum_required(VERSION 3.0.0)

set(PROJECT_NAME physics_lib)
set(LIBRARY_NAME physics_lib)

connect_lib(${LIBRARY_NAME} ${PROJECT_NAME} physics)

if (NOT (TARGET debug_lib))
    message(FATAL_ERROR "debug_lib targets NOT found")
endif()

if (NOT (TARGET math_lib))
    message(FATAL_ERROR "math_lib targets NOT found")
endif()

target_link_libraries(${LIBRARY_NAME} debug_lib)
target_link_libraries(${LIBRARY_NAME} math_lib)

add_subdirectory(test)