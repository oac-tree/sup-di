add_executable(unit-tests)

if(EXPLICIT_TEST_BUILD_DEPENDENCIES)
    add_dependencies(unit-tests sup-di sup-di-testservices)
endif()

configure_file(${CMAKE_CURRENT_LIST_DIR}/test_config.h.in ${SUP_DI_AUTOGEN_DIR}/test_config.h @ONLY)

target_sources(unit-tests
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/object_manager_tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/object_manager_external_tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/type_map_tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/type_string_list_tests.cpp
)

target_include_directories(unit-tests
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/../../../main/c++
        ${SUP_DI_AUTOGEN_DIR}
)

target_link_directories(unit-tests
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/../../../../target/lib
)

find_package(GTest REQUIRED)

target_link_libraries(unit-tests
    PRIVATE
        GTest::GTest
        GTest::Main
        gmock
        sup-di
        dl
)
