if(NOT COA_PARASOFT_INTEGRATION)
  return()
endif()

include(COASetupParasoft)

# Add parasoft project for sup-di-target
# This generates the build time information needed by Parasoft for analysis
cpptest_add_executable(sup-di-cpptest
  CPPTEST_PROJECT_LOC ${CMAKE_CURRENT_BINARY_DIR}
  CPPTEST_PROJECT_FOLDERS
  src-sup-di=${CMAKE_SOURCE_DIR}/src/lib/sup/di
  src-sup-di-composer-core=${CMAKE_SOURCE_DIR}/src/lib/sup/di-composer-core
  src-sup-di-services=${CMAKE_SOURCE_DIR}/src/lib/sup/di-services
  TARGETS sup-di sup-di-composer-core sup-di-services
)
get_target_property(SUP_di_INCLUDE_DIRECTORIES sup-di INCLUDE_DIRECTORIES)
target_include_directories(sup-di-cpptest PUBLIC ${SUP_di_INCLUDE_DIRECTORIES})
