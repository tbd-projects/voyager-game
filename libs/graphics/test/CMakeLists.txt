cmake_minimum_required(VERSION 3.0.0)

connect_test(graphics_lib_tests graphics_lib gtest)

find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(graphics_lib_tests ${SFML_LIBRARIES})
endif()
