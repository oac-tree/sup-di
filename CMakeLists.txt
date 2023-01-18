cmake_minimum_required(VERSION 3.5)

project(SUP-DI-PROJECT VERSION 0.1.0)

option(SUP_DI_EXPORT_BUILDTREE "Export build tree in /home/user/.cmake registry" OFF)
option(SUP_DI_CODAC "Compilation for CODAC environment" OFF)
option(COVERAGE "Generate unit test coverage information" FALSE)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/src/cmake)
include(configuration)

add_subdirectory(src/main/c++)
add_subdirectory(src/test/c++)

include(installation)
