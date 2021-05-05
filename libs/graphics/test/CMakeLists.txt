cmake_minimum_required(VERSION 3.0.0)

connect_test(graphics_lib_tests graphics_lib gtest)

target_link_libraries(graphics_lib_tests ${SFML_LIBRARIES})

find_package(SFML REQUIRED system window graphics)
#include_directories(${SFML_INCLUDE_DIR})
#target_link_libraries(graphics_lib_tests ${SFML_LIBRARIES})

find_package(Boost REQUIRED)
target_link_libraries(graphics_lib_tests ${Boost_LIBRARIES})

if (SFML_FOUND)
    message("URA")

endif()
message("${SFML_LIBRARIES}")
message("${SFML_LIBRARIES} ${SFML_DEPENDENCIES}")
target_link_libraries(graphics_lib_tests sfml-graphics sfml-window sfml-system)

