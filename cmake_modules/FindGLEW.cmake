#
# Find GLEW
#
# Try to find GLEW.
# This module defines:
# - GLEW_INCLUDE_DIRS
# - GLEW_LIBRARIES
# - GLEW_FOUND
#
# The following variables can be set as arguments for the module:
# - GLEW_ROOT_DIR: Root directory of GLEW
# - GLEW_USE_STATIC_LIBS: Specifies to use static versions of GLEW (Windows)
#

# Additional modules
include(FindPackageHandleStandardArgs)

if (WIN32)
    # Find include files
    find_path(
            GLEW_INCLUDE_DIR
            NAMES GL/glew.h
            PATHS
            $ENV{PROGRAMFILES}/include
            ${GLEW_ROOT_DIR}/include
            DOC "The directory where glew.h resides"
    )
	
    # Use glfw3.lib for static library
    if (GLEW_USE_STATIC_LIBS)
        set(GLEW_LIBRARY_NAME glew32s)
    else()
        set(GLEW_LIBRARY_NAME glew32)
    endif()

    # Find library files
    find_library(
            GLEW_LIBRARY
            NAMES ${GLEW_LIBRARY_NAME}
            PATHS
            $ENV{PROGRAMFILES}/lib
            ${GLEW_ROOT_DIR}/lib
            DOC "The GLEW library"
    )

    unset(GLEW_LIBRARY_NAME)
else()
    # Find include files
    find_path(
            GLEW_INCLUDE_DIR
            NAMES GL/glew.h
            PATHS
            /usr/include
            /usr/local/include
            /sw/include
            /opt/local/include
            ${GLEW_ROOT_DIR}/include
            DOC "The directory where glew.h resides"
    )

    # Find library files
    # Try to use static libraries
    find_library(
            GLEW_LIBRARY
            NAMES glew
            PATHS
            /usr/lib64
            /usr/lib
            /usr/lib/x86_64-linux-gnu
            /usr/local/lib64
            /usr/local/lib
            /sw/lib
            /opt/local/lib
            ${GLEW_ROOT_DIR}/lib
            DOC "The GLEW library"
    )
endif()

# Handle REQUIRED argument, define *_FOUND variable
find_package_handle_standard_args(
        GLEW
        DEFAULT_MSG
        GLEW_INCLUDE_DIR
        GLEW_LIBRARY
)

# Define ASSIMP_LIBRARIES and ASSIMP_INCLUDE_DIRS
if (GLEW_FOUND)
    set(GLEW_LIBRARIES ${GLEW_LIBRARY})
    set(GLEW_INCLUDE_DIRS ${GLEW_INCLUDE_DIR})
endif()

# Hide some variables
mark_as_advanced(GLEW_INCLUDE_DIR GLEW_LIBRARY)