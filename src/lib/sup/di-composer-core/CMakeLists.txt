set(library_name sup-di-composer-core)
set(export_name sup-di-composer-core)

add_library(${library_name} SHARED)
add_library(sup-di::${library_name} ALIAS ${library_name}) # alias for build-tree usage

set_target_properties(${library_name} PROPERTIES
    EXPORT_NAME ${export_name}
    SOVERSION ${LIBSOVERSION}
    VERSION ${LIBVERSION}
)

target_include_directories(${library_name} PUBLIC
  $<INSTALL_INTERFACE:include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../..>
)

target_sources(${library_name}
  PRIVATE
  composition_root.cpp
  double_instance_element.cpp
  element_constructor_map.cpp
  exceptions.cpp
  function_element.cpp
  i_composer_element.cpp
  instance_element.cpp
  integer_instance_element.cpp
  library_element.cpp
  object_composer_element.cpp
  string_instance_element.cpp
  tree_extract.cpp
)

find_package(sup-utils REQUIRED)

target_link_libraries(${library_name}
  PRIVATE
  sup-utils::sup-xml
  sup-di::sup-di
)

# -- Installation --
install(TARGETS ${library_name} EXPORT sup-di-targets LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
