cmake_minimum_required(VERSION 3.19)

set(PROJECT_NAME voyager)
set(SOURCE_DIR src)
set(SOURCE ${SOURCE_DIR}/main.cpp)
set(LIBRARIES_DIR libs)

#set(LIBRARIES A B)

set(CMAKE_CXX_STANDARD 14)

project(${PROJECT_NAME})

#########
# GTest #
#########
#enable_testing()
#add_subdirectory(libs/gtest-1.7.0)
#include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

###########
# Project #
###########

add_executable(${PROJECT_NAME} ${SOURCE})

foreach(LIBRARY ${LIBRARIES})
    add_subdirectory("${LIBRARIES_DIR}/${LIBRARY}")
endforeach(LIBRARY)
#
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})


