add_executable(sup-di-composer)

target_compile_features(sup-di-composer PRIVATE cxx_std_11)

target_include_directories(sup-di-composer
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

target_sources(sup-di-composer
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/main.cpp
        ${CMAKE_CURRENT_LIST_DIR}/utils.cpp
)

target_link_libraries(sup-di-composer
    PRIVATE
        sup-di
)

if (SUP_DI_CODAC)
  target_include_directories(sup-di-composer PUBLIC $ENV{CODAC_ROOT}/include)
  target_link_directories(sup-di-composer PUBLIC $ENV{CODAC_ROOT}/lib)
  target_link_libraries(sup-di-composer PRIVATE sup-xml)
else()
  find_package(sup-utils REQUIRED)
  target_link_libraries(sup-di-composer PRIVATE sup-utils::sup-xml)
endif()
