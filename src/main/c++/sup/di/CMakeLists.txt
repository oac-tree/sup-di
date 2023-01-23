add_library(sup-di SHARED)
add_library(sup-di::sup-di ALIAS sup-di) # alias for build-tree usage

target_compile_features(sup-di PRIVATE cxx_std_11)

set_target_properties(sup-di PROPERTIES
    VERSION ${LIBVERSION}
    SOVERSION ${LIBSOVERSION}
    OUTPUT_NAME sup-di
)

target_include_directories(sup-di PUBLIC
  $<INSTALL_INTERFACE:include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../..>)

target_sources(sup-di
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/error_codes.cpp
    ${CMAKE_CURRENT_LIST_DIR}/instance_container.cpp
    ${CMAKE_CURRENT_LIST_DIR}/object_manager.cpp
)

# -- Installation --

install(TARGETS sup-di EXPORT sup-di-targets LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
set_target_properties(sup-di PROPERTIES EXPORT_NAME sup-di)

install(FILES
    dependency_traits.h
    error_codes.h
    index_sequence.h
    instance_container.h
    object_manager.h
    type_functions.h
    type_map.h
    type_string_list.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/sup/di
)
