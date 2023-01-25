add_executable(unit-tests)

target_compile_features(unit-tests PRIVATE cxx_std_11)

target_sources(unit-tests
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/composition_root_tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/error_codes_tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/exceptions_tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/function_element_tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/global_test_environment.cpp
        ${CMAKE_CURRENT_LIST_DIR}/global_test_objects.cpp
        ${CMAKE_CURRENT_LIST_DIR}/instance_element_tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/library_element_tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/object_composer_element_tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/object_manager_tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/object_manager_external_tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/string_instance_element_tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/tree_extract_tests.cpp
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
        sup-di-composer-core
        sup-di
        dl
)
