add_executable(sup-di-composer)

target_compile_features(sup-di-composer PRIVATE cxx_std_11)

target_include_directories(sup-di-composer
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/../../lib
)

target_sources(sup-di-composer
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp
)

target_link_libraries(sup-di-composer
  PRIVATE
    sup-di-composer-core
)
