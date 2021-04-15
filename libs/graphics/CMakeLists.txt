cmake_minimum_required(VERSION 3.0.0)

set(PROJECT_NAME graphics_lib)
set(LIBRARY_NAME graphics_lib)

connect_lib(${LIBRARY_NAME} ${PROJECT_NAME} graphics)

find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${LIBRARY_NAME} ${SFML_LIBRARIES})
endif()

#add_subdirectory(test)
