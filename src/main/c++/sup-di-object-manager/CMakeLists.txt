cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Weffc++ -pedantic")
if (COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g -fprofile-arcs -ftest-coverage --coverage")
endif()

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

add_executable(sup-di-object-manager)

target_include_directories(sup-di-object-manager
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

target_sources(sup-di-object-manager
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/main.cpp
)