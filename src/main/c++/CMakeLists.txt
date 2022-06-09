cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g -fprofile-arcs -ftest-coverage --coverage")
endif()

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

add_library(sup-di SHARED)

target_include_directories(sup-di
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

add_subdirectory(sup)

set_target_properties(sup-di PROPERTIES
    VERSION ${LIBVERSION}
    SOVERSION ${LIBSOVERSION}
    OUTPUT_NAME sup-di
)

install(DIRECTORY sup/di/
        DESTINATION include/sup/di
        FILES_MATCHING PATTERN "*.h")