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
# SPDX-License-Identifier: MIT
#
# This file is part of ITER CODAC software.
# For the terms and conditions of redistribution or use of this software
# refer to the file LICENSE located in the top level directory
# of the distribution package.

cmake_minimum_required(VERSION 3.13...3.31)
project(sup-di-project VERSION 1.5.0)

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

include(packaging)
