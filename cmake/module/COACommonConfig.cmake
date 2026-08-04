# -----------------------------------------------------------------------------
# Main project configuration
# -----------------------------------------------------------------------------

include(GNUInstallDirs)
include(CTest)

# -----------------------------------------------------------------------------
# C++ version
# -----------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
  if(COA_COVERAGE)
    # Coverage must be built unoptimized: at -O2 gcc emits IPA-SRA (".isra") clones for functions
    # with unused parameters, and gcov then attributes their execution to the clone, reporting the
    # originals as never executed and undercounting coverage.
    set(CMAKE_BUILD_TYPE "Debug")
  else()
    set(CMAKE_BUILD_TYPE "RelWithDebInfo")
  endif()
endif()

if(COA_COVERAGE)
  # Instrument the whole project (library AND tests). Header-defined templates and inline functions
  # are compiled into whichever translation unit instantiates them; when that is a test TU, the
  # executed lines only appear in coverage if the test TU is instrumented too. Setting the flags
  # here (before any add_subdirectory) applies them to every subdirectory.
  message(STATUS "Enabling test coverage information")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g -fno-inline --coverage")
endif()

# -----------------------------------------------------------------------------
# Variables
# -----------------------------------------------------------------------------
set(LIBVERSION ${PROJECT_VERSION})
set(LIBSOVERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})

# -----------------------------------------------------------------------------
# Directories
# -----------------------------------------------------------------------------
if(NOT DEFINED TEST_OUTPUT_DIRECTORY)
  set(TEST_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/test_bin)
endif()

file(MAKE_DIRECTORY ${TEST_OUTPUT_DIRECTORY})
