macro( connect_test project_test_name lib_name main_project_test_name )
    project(${project_test_name})

    enable_testing()

    file(GLOB TESTS_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp)

    get_property(tmp GLOBAL PROPERTY GTEST_SOURCE_TEST_DIR)

    if (NOT (tmp))
        message(FATAL_ERROR "NOT found variable GTEST_SOURCE_TEST_DIR for test source")
    endif()

    set(tmp ${tmp} ${TESTS_SOURCE})

    set_property(GLOBAL PROPERTY GTEST_SOURCE_TEST_DIR ${tmp})

    add_executable(${project_test_name} ${CMAKE_CURRENT_SOURCE_DIR}/test_main.cpp ${TESTS_SOURCE})

    target_link_libraries(${project_test_name} ${lib_name} ${GTEST_LIBRARIES} pthread gmock)

    #add_test(${project_test_name} ${project_test_name})

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