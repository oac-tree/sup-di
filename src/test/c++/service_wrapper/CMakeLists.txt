add_library(service-wrapper SHARED)

configure_file(${CMAKE_CURRENT_LIST_DIR}/example.xml.in ${SUP_DI_AUTOGEN_DIR}/example.xml @ONLY)

target_compile_features(service-wrapper PRIVATE cxx_std_11)

set_target_properties(service-wrapper PROPERTIES
    VERSION ${LIBVERSION}
    SOVERSION ${LIBSOVERSION}
    OUTPUT_NAME service-wrapper
)

target_sources(service-wrapper
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/registration.cpp
        ${CMAKE_CURRENT_LIST_DIR}/services.cpp
)

target_include_directories(service-wrapper
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(service-wrapper
    PRIVATE
        sup-di
)
