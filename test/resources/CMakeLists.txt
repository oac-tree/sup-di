cmake_minimum_required(VERSION 3.13)

project(test-printing-example
        VERSION 1.0
        LANGUAGES CXX)

add_library(test-printing SHARED)

target_compile_features(test-printing PRIVATE cxx_std_11)

set_target_properties(test-printing PROPERTIES
    OUTPUT_NAME test-printing
)

target_sources(test-printing
    PRIVATE
    registration.cpp
)

target_include_directories(test-printing
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

find_package(sup-di REQUIRED)

target_link_libraries(test-printing
    PRIVATE
    sup-di::sup-di
)
