add_executable(sup-di-composer)

target_compile_features(sup-di-composer PRIVATE cxx_std_11)

target_include_directories(sup-di-composer
  PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
)

target_sources(sup-di-composer
  PRIVATE
  main.cpp
)

target_link_libraries(sup-di-composer
  PRIVATE
  sup-di-composer-core
)

# -- Installation --
install(TARGETS sup-di-composer RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
