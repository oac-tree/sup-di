cmake_minimum_required(VERSION 3.5)

project(SUP-DI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g -fprofile-arcs -ftest-coverage --coverage")
endif()

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

# add_library(sup-di SHARED)

# add_subdirectory(include)

# set_target_properties(sup-di PROPERTIES
#     VERSION ${LIBVERSION}
#     SOVERSION ${LIBSOVERSION}
#     OUTPUT_NAME sup-di
# )

# install(TARGETS sup-di DESTINATION lib)
install(DIRECTORY include/ DESTINATION include
        FILES_MATCHING PATTERN "*.h")