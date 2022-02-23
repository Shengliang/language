cmake_minimum_required (VERSION 3.22)
project (Tutorial)

# The version number.
set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/include/TutorialConfig.h.in"
  "${PROJECT_BINARY_DIR}/TutorialConfig.h"
  )

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories ("${PROJECT_BINARY_DIR}")


# Add a custom command that produces src/git_version.cc
add_custom_command (
    OUTPUT ${PROJECT_SOURCE_DIR}/src/git_version.cc
    COMMAND ${PROJECT_SOURCE_DIR}/src/gen_version.sh
    ARGS ${PROJECT_SOURCE_DIR}/src/git_version.cc
) 

# add the executable
add_executable (Tutorial src/git_version.cc src/hello.cc)
