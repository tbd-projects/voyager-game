cmake_minimum_required(VERSION 3.1X)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Wpedantic -ggdb3")

set(PROJECT_NAME voyager)
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(SOURCE ${SOURCE_DIR}/main.cpp)
set(LIBRARIES_DIR ${CMAKE_SOURCE_DIR}/libs)
cmake_policy(SET CMP0079 NEW)
set(LIBRARIES debug_lib math_lib physics_lib loaders_lib math_external_lib
        shop_lib event_controller_lib game_manager_lib game_lib sf_graphics_lib graphics_lib menu_lib)

project(${PROJECT_NAME})

########
# CodeCoverage #
########
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake-modules")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake-utilits")

include(templates)
include(CodeCoverage)
append_coverage_compiler_flags()

#########
# GTest #
#########

#enable_testing()
find_package(GTest)
include_directories(${GTEST_INCLUDE_DIRS})

#set(GTEST_SOURCE_TEST_DIR ${CMAKE_SOURCE_DIR}/src/test_main.cpp )
set_property(GLOBAL PROPERTY GTEST_SOURCE_TEST_DIR ${CMAKE_SOURCE_DIR}/src/test_main.cpp)
#####################
# Fix for old gtest #
#####################

add_definitions(-DINSTANTIATE_TEST_SUITE_P=INSTANTIATE_TEST_CASE_P)
add_definitions(-DBOOST_BIND_GLOBAL_PLACEHOLDERS)
###########
# Project #
###########

add_executable(${PROJECT_NAME} ${SOURCE})

foreach(LIBRARY ${LIBRARIES})
    string(REPLACE "_lib" "" LIBRARY ${LIBRARY})
    add_subdirectory("${LIBRARIES_DIR}/${LIBRARY}")
endforeach(LIBRARY)

target_link_libraries(math_lib debug_lib)
target_link_libraries(math_external_lib math_lib debug_lib game_manager_lib)
target_link_libraries(physics_lib debug_lib math_lib game_manager_lib)
target_link_libraries(game_manager_lib debug_lib menu_lib game_lib sf_graphics_lib graphics_lib)
target_link_libraries(loaders_lib game_manager_lib math_lib game_lib debug_lib)

target_link_libraries(menu_lib graphics_lib event_controller_lib game_manager_lib)

target_link_libraries(game_lib loaders_lib)

target_link_libraries(graphics_lib math_lib game_manager_lib)
target_link_libraries(sf_graphics_lib graphics_lib sfml-graphics sfml-window sfml-system)
target_link_libraries(graphics_lib_tests sf_graphics_lib)
target_link_libraries(menu_lib_tests sf_graphics_lib)
target_link_libraries(game_manager_lib_tests sf_graphics_lib math_external_lib)

target_link_libraries(event_controller_lib graphics_lib game_manager_lib)

target_link_libraries(${PROJECT_NAME} ${LIBRARIES})

get_property(tmp GLOBAL PROPERTY GTEST_SOURCE_TEST_DIR)

add_executable(gtest ${tmp})
target_link_libraries(gtest ${LIBRARIES} ${GTEST_LIBRARIES} pthread gmock)
#add_test(gtest gtest)

setup_target_for_coverage_lcov (
        NAME coverage
        EXECUTABLE gtest
        BASE_DIRECTORY "${PROJECT_SOURCE_DIR}"
        EXCLUDE "/usr/*" ${tmp} "/*/*.hpp"
)
