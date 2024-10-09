add_library(sup-di-testservices SHARED)

configure_file(${CMAKE_CURRENT_LIST_DIR}/test_config.h.in ${SUP_DI_AUTOGEN_DIR}/test_config.h @ONLY)

set_target_properties(sup-di-testservices PROPERTIES
    VERSION ${LIBVERSION}
    SOVERSION ${LIBSOVERSION}
    OUTPUT_NAME sup-di-testservices
)

target_sources(sup-di-testservices
    PRIVATE
    external_test_services.cpp
)

target_include_directories(sup-di-testservices
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(sup-di-testservices
    PRIVATE
    sup-di
)
