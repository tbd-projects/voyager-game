cmake_minimum_required(VERSION 3.1X)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Werror -Wpedantic -Wpadded -ggdb3")

set(PROJECT_NAME voyager)
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(SOURCE ${SOURCE_DIR}/main.cpp)
set(LIBRARIES_DIR ${CMAKE_SOURCE_DIR}/libs)
cmake_policy(SET CMP0079 NEW)
set(LIBRARIES debug_lib math_lib physics_lib loaders_lib graphics_lib
        shop_lib event_controller_lib game_manager_lib menu_lib game_lib)
#set(LIBRARIES A B)

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
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(gtest ${CMAKE_SOURCE_DIR}/src/test_main.cpp)
target_link_libraries(gtest ${GTEST_LIBRARIES} pthread)
add_test(gtest gtest)

###########
# Project #
###########

add_executable(${PROJECT_NAME} ${SOURCE})

add_subdirectory("${LIBRARIES_DIR}/debug")
add_subdirectory("${LIBRARIES_DIR}/loaders")
add_subdirectory("${LIBRARIES_DIR}/math")
add_subdirectory("${LIBRARIES_DIR}/physics")
add_subdirectory("${LIBRARIES_DIR}/graphics")
add_subdirectory("${LIBRARIES_DIR}/shop")
add_subdirectory("${LIBRARIES_DIR}/event_controller")
add_subdirectory("${LIBRARIES_DIR}/menu")
add_subdirectory("${LIBRARIES_DIR}/game")
add_subdirectory("${LIBRARIES_DIR}/game_manager")

target_link_libraries(${PROJECT_NAME} ${LIBRARIES})

#setup_target_for_coverage_lcov (
#        NAME coverage
#        EXECUTABLE gtest
#        BASE_DIRECTORY "${PROJECT_SOURCE_DIR}"
#        EXCLUDE "/usr/*"
#)



