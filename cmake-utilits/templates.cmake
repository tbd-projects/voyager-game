macro( connect_test project_test_name lib_name main_project_test_name )
    project(${project_test_name})

    enable_testing()

    file(GLOB LIBRARY_TESTS_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp)

    if (NOT (TARGET ${main_project_test_name}))
        message(FATAL_ERROR "${main_project_test_name} targets NOT found")
    endif()

    if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests")

#        add_library("${project_test_name}_lib" STATIC ${LIBRARY_TESTS_SOURCE})

        add_executable(${project_test_name} "${CMAKE_CURRENT_SOURCE_DIR}/test_main.cpp"  ${LIBRARY_TESTS_SOURCE})

        target_include_directories(${project_test_name} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include" "${CMAKE_CURRENT_SOURCE_DIR}/include")
#        target_include_directories(${project_test_name}_lib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include" "${CMAKE_CURRENT_SOURCE_DIR}/include")

        target_link_libraries(${project_test_name} ${lib_name} ${GTEST_LIBRARIES} pthread)

        target_link_libraries(${main_project_test_name} ${lib_name})

    else()

        add_executable(${project_test_name} ${LIBRARY_TESTS_SOURCE} "${CMAKE_CURRENT_SOURCE_DIR}/test_main.cpp")

        target_link_libraries(${project_test_name} ${lib_name} ${GTEST_LIBRARIES} pthread)

    endif()

endmacro( connect_test )


macro( connect_lib lib_name project_name include_lib_name)
    set(LIBRARY_HEADERS_DIR include/${lib_name})
    file(GLOB LIBRARY_HEADERS ${LIBRARY_HEADERS_DIR}/*.h)

    set(LIBRARY_SOURCE_DIR src)
    file(GLOB LIBRARY_SOURCE ${LIBRARY_SOURCE_DIR}/*.cpp)

    project(${project_name})

    add_library(${lib_name} STATIC ${LIBRARY_HEADERS} ${LIBRARY_SOURCE})

    target_include_directories(${lib_name} PRIVATE
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/${include_lib_name}>
            $<INSTALL_INTERFACE:include/${include_lib_name}>
            )

    target_include_directories(${lib_name} PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:include>
            )

endmacro( connect_lib )