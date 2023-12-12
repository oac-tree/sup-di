add_executable(unit-tests)

target_compile_features(unit-tests PRIVATE cxx_std_11)

target_sources(unit-tests
    PRIVATE
    composition_root_tests.cpp
    dependency_traits_tests.cpp
    error_codes_tests.cpp
    exceptions_tests.cpp
    function_element_tests.cpp
    global_test_environment.cpp
    global_test_objects.cpp
    index_sequence_tests.cpp
    instance_element_tests.cpp
    library_element_tests.cpp
    object_composer_element_tests.cpp
    object_manager_tests.cpp
    object_manager_external_tests.cpp
    string_instance_element_tests.cpp
    temporary_file.cpp
    tree_extract_tests.cpp
    type_map_tests.cpp
    type_string_list_tests.cpp
)

target_include_directories(unit-tests
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${SUP_DI_AUTOGEN_DIR}
)

find_package(GTest REQUIRED)

find_package(sup-utils REQUIRED)

target_link_libraries(unit-tests
    PRIVATE
    GTest::GTest
    GTest::Main
    sup-utils::sup-xml
    sup-di-composer-core
    sup-di
    dl
)

set_target_properties(unit-tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TEST_OUTPUT_DIRECTORY})
