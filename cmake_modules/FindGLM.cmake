#
# Find GLM
#
# Try to find GLM, The OpenGL Mathematics Library
# This module defines:
# - GLM_INCLUDE_DIRS
# - GLM_FOUND
#
# The following variables can be set as arguments for the module:
# - GLM_ROOT_DIR: Root directory of GLM
#
# Source:
# - https://github.com/lighttransport/nanogi/blob/master/cmake/FindGLM.cmake
#

# Additional modules
include(FindPackageHandleStandardArgs)

if (WIN32)
    # Find include files
    find_path(
            GLM_INCLUDE_DIR
            NAMES glm/glm.hpp
            PATHS
            $ENV{PROGRAMFILES}/include
            ${GLM_ROOT_DIR}/include
            DOC "The directory where glm/glm.hpp resides"
    )
else()
    # Find include files
    find_path(
            GLM_INCLUDE_DIR
            NAMES glm/glm.hpp
            PATHS
            /usr/include
            /usr/local/include
            /sw/include
            /opt/local/include
            ${GLM_ROOT_DIR}/include
            DOC "The directory where glm/glm.hpp resides"
    )
endif()

# Handle REQUIRED argument, define *_FOUND variable
find_package_handle_standard_args(GLM DEFAULT_MSG GLM_INCLUDE_DIR)

# Define GLM_INCLUDE_DIRS
if (GLM_FOUND)
    set(GLM_INCLUDE_DIRS ${GLM_INCLUDE_DIR})
endif()

# Hide some variables
mark_as_advanced(GLM_INCLUDE_DIR)