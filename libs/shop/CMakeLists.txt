cmake_minimum_required(VERSION 3.0.0)

set(PROJECT_NAME shop_lib)
set(LIBRARY_NAME shop_lib)

connect_lib(${LIBRARY_NAME} ${PROJECT_NAME} shop)

if (NOT (TARGET loaders_lib))
    message(FATAL_ERROR "loaders_lib targets NOT found")
endif ()

target_link_libraries(${LIBRARY_NAME} loaders_lib)


add_subdirectory(test)