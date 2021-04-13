cmake_minimum_required(VERSION 3.1X)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Werror -Wpedantic -Wpadded -ggdb3")

set(PROJECT_NAME voyager)
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(SOURCE ${SOURCE_DIR}/main.cpp)
set(LIBRARIES_DIR ${CMAKE_SOURCE_DIR}/libs)

#set(LIBRARIES A B)

project(${PROJECT_NAME})

########
# CodeCoverage #
########
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake-modules")

include(CodeCoverage)
append_coverage_compiler_flags()

#########
# GTest #
#########
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
###########
# Project #
###########

add_executable(${PROJECT_NAME} ${SOURCE})

foreach(LIBRARY ${LIBRARIES})
    add_subdirectory("${LIBRARIES_DIR}/${LIBRARY}")
endforeach(LIBRARY)

target_link_libraries(${PROJECT_NAME} ${LIBRARIES})

#setup_target_for_coverage_lcov (
#        NAME coverage
#        EXECUTABLE gtest
#        BASE_DIRECTORY "${PROJECT_SOURCE_DIR}"
#        EXCLUDE "/usr/*"
#)



