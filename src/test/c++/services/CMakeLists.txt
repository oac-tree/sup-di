add_library(sup-di-testservices SHARED)

set_target_properties(sup-di-testservices PROPERTIES
    VERSION ${LIBVERSION}
    SOVERSION ${LIBSOVERSION}
    OUTPUT_NAME sup-di-testservices
)

target_sources(sup-di-testservices
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/external_test_services.cpp
)

target_include_directories(sup-di-testservices
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(sup-di-testservices
    PRIVATE
        sup-di
)

install(TARGETS sup-di-testservices LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
set_target_properties(sup-di-testservices PROPERTIES EXPORT_NAME sup-di-testservices)
