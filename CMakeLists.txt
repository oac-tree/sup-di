cmake_minimum_required(VERSION 3.5)

project(SUP-DI-PROJECT VERSION 1.0.0)

option(SUP_DI_EXPORT_BUILDTREE "Export build tree in /home/user/.cmake registry" OFF)
option(NO_CODAC "Don't look for the presence of CODAC environment" OFF)
option(COVERAGE "Generate unit test coverage information" FALSE)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/src/cmake)
include(configuration)

add_subdirectory(src)
add_subdirectory(test)

include(installation)
