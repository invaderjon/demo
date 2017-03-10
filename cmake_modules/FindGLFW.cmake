#
# Find GLM
#
# Try to find GLM, The OpenGL Mathematics Library
# This module defines:
# - GLFW_INCLUDE_DIRS
# - GLFW_LIBRARIES
# - GLFW_FOUND
#
# The following variables can be set as arguments for the module:
# - GLFW_ROOT_DIR: Root directory of GLFW
# - GLFW_USE_STATIC_LIBS: Specifies to use static versions of GLFW (Windows)
#
# Source:
# - https://github.com/lighttransport/nanogi/blob/master/cmake/FindGLFW.cmake
#

# Additional modules
include(FindPackageHandleStandardArgs)

if (WIN32)
    # Find include files
    find_path(
            GLFW_INCLUDE_DIR
            NAMES GLFW/glfw3.h
            PATHS
            ${CMAKE_SOURCE_DIR}/include
            $ENV{PROGRAMFILES}/include
            ${GLFW_ROOT_DIR}/include
            DOC "The directory where GLFW/glfw.h resides"
    )

    # Use glfw3.lib for static library
    if (GLFW_USE_STATIC_LIBS)
        set(GLFW_LIBRARY_NAME glfw3)
    else()
        set(GLFW_LIBRARY_NAME glfw3dll)
    endif()

    # Find library files
    find_library(
            GLFW_LIBRARY
            NAMES ${GLFW_LIBRARY_NAME}
            PATHS
            ${CMAKE_SOURCE_DIR}/lib
            $ENV{PROGRAMFILES}/lib
            ${GLFW_ROOT_DIR}/lib
            DOC "The GLFW library"
    )

    unset(GLFW_LIBRARY_NAME)
else()
    # Find include files
    find_path(
            GLFW_INCLUDE_DIR
            NAMES GLFW/glfw3.h
            PATHS
            /usr/include
            /usr/local/include
            /sw/include
            /opt/local/include
            ${CMAKE_SOURCE_DIR}/include
            ${GLFW_ROOT_DIR}/include
            DOC "The directory where GLFW/glfw3.h resides"
    )

    # Find library files
    # Try to use static libraries
    find_library(
            GLFW_LIBRARY
            NAMES glfw
            PATHS
            /usr/lib64
            /usr/lib
            /usr/lib/x86_64-linux-gnu
            /usr/local/lib64
            /usr/local/lib
            /sw/lib
            /opt/local/lib
            ${CMAKE_SOURCE_DIR}/lib
            ${GLFW_ROOT_DIR}/lib
            DOC "The GLFW library"
    )
endif()

# Handle REQUIRED argument, define *_FOUND variable
find_package_handle_standard_args(
        GLFW
        DEFAULT_MSG
        GLFW_INCLUDE_DIR
        GLFW_LIBRARY
)

# Define GLFW_LIBRARIES and GLFW_INCLUDE_DIRS
if (GLFW_FOUND)
    set(GLFW_LIBRARIES ${OPENGL_LIBRARIES} ${GLFW_LIBRARY})
    set(GLFW_INCLUDE_DIRS ${GLFW_INCLUDE_DIR})
endif()

# Hide some variables
mark_as_advanced(GLFW_INCLUDE_DIR GLFW_LIBRARY)