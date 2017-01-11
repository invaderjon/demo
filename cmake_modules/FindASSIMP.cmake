#
# Find Assimp
#
# Try to find Assimp, The Open Asset Import Library
# This module defines:
# - ASSIMP_INCLUDE_DIRS
# - ASSIMP_LIBRARIES
# - ASSIMP_FOUND
#
# The following variables can be set as arguments for the module:
# - ASSIMP_ROOT_DIR: Root directory of Assimp
# - ASSIMP_USE_STATIC_LIBS: Specifies to use static versions of Assimp (Windows)
#

# Additional modules
include(FindPackageHandleStandardArgs)

if (WIN32)
    # Find include files
    find_path(
            ASSIMP_INCLUDE_DIR
            NAMES assimp/version.h
            PATHS
            $ENV{PROGRAMFILES}/include
            ${ASSIMP_ROOT_DIR}/include
            DOC "The directory where assimp/version.h resides"
    )

    # Use assimp.lib for static library
    if (ASSIMP_USE_STATIC_LIBS)
        set(ASSIMP_LIBRARY_NAME assimp)
    else()
        set(ASSIMP_LIBRARY_NAME assimpdll)
    endif()

    # Find library files
    find_library(
            ASSIMP_LIBRARY
            NAMES ${ASSIMP_LIBRARY_NAME}
            PATHS
            $ENV{PROGRAMFILES}/lib
            ${ASSIMP_ROOT_DIR}/lib
            DOC "The Assimp library"
    )

    unset(ASSIMP_LIBRARY_NAME)
else()
    # Find include files
    find_path(
            ASSIMP_INCLUDE_DIR
            NAMES assimp/version.h
            PATHS
            /usr/include
            /usr/local/include
            /sw/include
            /opt/local/include
            ${ASSIMP_ROOT_DIR}/include
            DOC "The directory where assimp/version.h resides"
    )

    # Find library files
    # Try to use static libraries
    find_library(
            ASSIMP_LIBRARY
            NAMES assimp
            PATHS
            /usr/lib64
            /usr/lib
            /usr/lib/x86_64-linux-gnu
            /usr/local/lib64
            /usr/local/lib
            /sw/lib
            /opt/local/lib
            ${ASSIMP_ROOT_DIR}/lib
            DOC "The Assimp library"
    )
endif()

# Handle REQUIRED argument, define *_FOUND variable
find_package_handle_standard_args(
        ASSIMP
        DEFAULT_MSG
        ASSIMP_INCLUDE_DIR
        ASSIMP_LIBRARY
)

# Define ASSIMP_LIBRARIES and ASSIMP_INCLUDE_DIRS
if (ASSIMP_FOUND)
    set(ASSIMP_LIBRARIES ${ASSIMP_LIBRARY})
    set(ASSIMP_INCLUDE_DIRS ${ASSIMP_INCLUDE_DIR})
endif()

# Hide some variables
mark_as_advanced(ASSIMP_INCLUDE_DIR ASSIMP_LIBRARY)