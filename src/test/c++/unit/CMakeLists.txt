add_executable(unit-tests)

target_compile_features(sup-di-testservices PRIVATE cxx_std_11)

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
        ${SUP_DI_AUTOGEN_DIR}
)

find_package(GTest REQUIRED)

target_link_libraries(unit-tests
    PRIVATE
        GTest::GTest
        GTest::Main
        sup-di
        dl
)
