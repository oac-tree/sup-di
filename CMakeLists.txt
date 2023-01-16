cmake_minimum_required(VERSION 3.5)

project(SUP-DI-PROJECT VERSION 0.1.0)

option(COVERAGE "Generate unit test coverage information" FALSE)
option(SUP_DI_EXPORT_BUILDTREE "Export build tree in /home/user/.cmake registry" OFF)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/src/cmake)
include(configuration)

add_subdirectory(src/main/c++)
add_subdirectory(src/test/c++)

include(installation)
