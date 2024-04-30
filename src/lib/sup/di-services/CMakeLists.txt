set(library_name sup-di-services)
set(export_name sup-di-services)

add_library(${library_name} SHARED)
add_library(sup-di::${library_name} ALIAS ${library_name}) # alias for build-tree usage

target_compile_features(${library_name} PRIVATE cxx_std_11)

set_target_properties(${library_name} PROPERTIES
    EXPORT_NAME ${export_name}
    SOVERSION ${LIBSOVERSION}
    VERSION ${LIBVERSION}
)

target_include_directories(${library_name} PUBLIC
  $<INSTALL_INTERFACE:include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../..>)

target_sources(${library_name}
  PRIVATE
  keep_alive.cpp
  registration.cpp
)

target_link_libraries(${library_name}
  PRIVATE
  sup-di::sup-di
)

# -- Installation --
install(TARGETS ${library_name} EXPORT sup-di-targets LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(FILES
  registered_names.h
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/sup/di/services
)
