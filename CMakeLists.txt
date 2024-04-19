# Project       : Supervision and Automation - Dependency injection
#
# Description   : The definition and implementation for dependency injection templates in SUP.
#
# Author        : Walter Van Herck (IO)
#
# Copyright (c) : 2010-2025 ITER Organization,
#                 CS 90 046
#                 13067 St. Paul-lez-Durance Cedex
#                 France
#
# This file is part of ITER CODAC software.
# For the terms and conditions of redistribution or use of this software
# refer to the file ITER-LICENSE.TXT located in the top level directory
# of the distribution package.

cmake_minimum_required(VERSION 3.13...3.31)
project(sup-di-project VERSION 1.4.0)

option(COVERAGE "Generate unit test coverage information" OFF)
option(COA_EXPORT_BUILD_TREE "Export build tree in /home/user/.cmake registry" OFF)
option(COA_BUILD_TESTS "Build unit tests" ON)
option(COA_BUILD_DOCUMENTATION "Build documentation" OFF)
option(COA_NO_CODAC "Don't look for the presence of CODAC environment" OFF)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake/module)
set(CMAKE_CONFIG_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake/config)
include(configuration)

add_subdirectory(src)

if(COA_BUILD_TESTS)
  add_subdirectory(test)
endif()

add_subdirectory(doc)

include(installation)

# set(CPACK_PACKAGE_VERSION ${CMAKE_PROJECT_VERSION})
# set(CPACK_GENERATOR "RPM")
# set(CPACK_PACKAGE_NAME "sup-di")
# set(CPACK_PACKAGE_RELEASE 0)
# set(CPACK_PACKAGE_CONTACT "ITER Organization")
# set(CPACK_PACKAGE_VENDOR "ITER Organization")
# set(CPACK_PACKAGING_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})
# set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_PACKAGE_RELEASE}.${CMAKE_SYSTEM_PROCESSOR}")
# set(RPM_BUILD_ROOT ${CMAKE_CURRENT_BINARY_DIR})

# configure_file("${CMAKE_CURRENT_SOURCE_DIR}/project.spec.in" "${CMAKE_CURRENT_BINARY_DIR}/project.spec" @ONLY IMMEDIATE)
# set(CPACK_RPM_USER_BINARY_SPECFILE "${CMAKE_CURRENT_BINARY_DIR}/project.spec")
# include(CPack)