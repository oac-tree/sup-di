add_library(sup-di-testservices SHARED)

set_target_properties(sup-di-testservices PROPERTIES
    VERSION ${LIBVERSION}
    SOVERSION ${LIBSOVERSION}
    OUTPUT_NAME sup-di-testservices
)

if(EXPLICIT_TEST_BUILD_DEPENDENCIES)
    add_dependencies(sup-di-testservices sup-di)
endif()

target_sources(sup-di-testservices
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/ExternalTestServices.cpp
)

target_include_directories(sup-di-testservices
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/../../../main/c++/include
)

target_link_directories(sup-di-testservices
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/../../../../target/lib
)

target_link_libraries(sup-di-testservices
    PRIVATE
        sup-di
)
