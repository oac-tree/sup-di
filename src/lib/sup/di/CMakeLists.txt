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
  di_utils.cpp
  error_codes.cpp
  instance_container.cpp
  object_manager.cpp
)

target_link_libraries(sup-di
  PUBLIC
  dl
)

# -- Installation --
install(TARGETS sup-di EXPORT sup-di-targets LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
set_target_properties(sup-di PROPERTIES EXPORT_NAME sup-di)

install(FILES
  di_utils.h
  error_codes.h
  forwarding_type_traits.h
  index_sequence.h
  injection_type_traits.h
  instance_container.h
  object_manager.h
  ownership_traits.h
  service_store.h
  storage_type_traits.h
  template_utils.h
  type_list.h
  type_map.h
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/sup/di
)
