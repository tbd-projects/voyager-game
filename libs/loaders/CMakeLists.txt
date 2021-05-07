cmake_minimum_required(VERSION 3.0.0)

set(PROJECT_NAME loaders_lib)
set(LIBRARY_NAME loaders_lib)

connect_lib(${LIBRARY_NAME} ${PROJECT_NAME} loaders)

if (NOT (TARGET shop_lib))
    message(FATAL_ERROR "shop_lib targets NOT found")
endif ()

target_link_libraries(${LIBRARY_NAME} game_lib)
target_link_libraries(${LIBRARY_NAME} shop_lib)


add_subdirectory(test)