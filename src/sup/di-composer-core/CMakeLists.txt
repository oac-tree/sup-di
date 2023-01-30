add_library(sup-di-composer-core STATIC)

target_compile_features(sup-di-composer-core PRIVATE cxx_std_11)

target_include_directories(sup-di-composer-core
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

target_sources(sup-di-composer-core
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/composition_root.cpp
    ${CMAKE_CURRENT_LIST_DIR}/element_constructor_map.cpp
    ${CMAKE_CURRENT_LIST_DIR}/exceptions.cpp
    ${CMAKE_CURRENT_LIST_DIR}/function_element.cpp
    ${CMAKE_CURRENT_LIST_DIR}/i_composer_element.cpp
    ${CMAKE_CURRENT_LIST_DIR}/instance_element.cpp
    ${CMAKE_CURRENT_LIST_DIR}/library_element.cpp
    ${CMAKE_CURRENT_LIST_DIR}/object_composer_element.cpp
    ${CMAKE_CURRENT_LIST_DIR}/string_instance_element.cpp
    ${CMAKE_CURRENT_LIST_DIR}/tree_extract.cpp
)

find_package(sup-utils REQUIRED)

target_link_libraries(sup-di-composer-core
  PRIVATE
    sup-utils::sup-xml
    sup-di
    dl
)
