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

add_library(sup-di SHARED)

add_library(sup-di::sup-di ALIAS sup-di) # alias for build-tree usage

add_subdirectory(sup)

set_target_properties(sup-di PROPERTIES
    VERSION ${LIBVERSION}
    SOVERSION ${LIBSOVERSION}
    OUTPUT_NAME sup-di
)

target_include_directories(sup-di PUBLIC
  $<INSTALL_INTERFACE:include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)

install(TARGETS sup-di EXPORT sup-di-targets LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
set_target_properties(sup-di PROPERTIES EXPORT_NAME sup-di)

install(FILES
        sup/di/dependency_traits.h
        sup/di/error_codes.h
        sup/di/index_sequence.h
        sup/di/instance_container.h
        sup/di/object_manager.h
        sup/di/type_map.h
        sup/di/type_string_list.h
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/sup/di)
