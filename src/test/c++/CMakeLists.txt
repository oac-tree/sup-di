cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g -fprofile-arcs -ftest-coverage --coverage")
endif()

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

set(SUP_DI_AUTOGEN_DIR ${CMAKE_BINARY_DIR}/autogen)
file(MAKE_DIRECTORY ${SUP_DI_AUTOGEN_DIR})

add_subdirectory(services)
add_subdirectory(unit)
