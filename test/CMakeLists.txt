if (COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g -fprofile-arcs -ftest-coverage --coverage")
endif()

set(SUP_DI_AUTOGEN_DIR ${CMAKE_CURRENT_BINARY_DIR}/autogen)
file(MAKE_DIRECTORY ${SUP_DI_AUTOGEN_DIR})

add_subdirectory(service_wrapper)
add_subdirectory(services)
add_subdirectory(unit)

file(WRITE ${TEST_OUTPUT_DIRECTORY}/test.sh
"#!/bin/bash
" ${TEST_OUTPUT_DIRECTORY} "/unit-tests \"$@\"
exit $?
")

configure_file(${TEST_OUTPUT_DIRECTORY}/test.sh ${TEST_OUTPUT_DIRECTORY}/test.sh
               FILE_PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ)
