add_library(sup-di-composer-core STATIC)

target_compile_features(sup-di-composer-core PRIVATE cxx_std_11)

target_include_directories(sup-di-composer-core PUBLIC
  $<INSTALL_INTERFACE:include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../..>
)

target_sources(sup-di-composer-core
  PRIVATE
  composition_root.cpp
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

target_link_libraries(sup-di-composer-core
  PRIVATE
  sup-utils::sup-xml
  sup-di::sup-di
)
