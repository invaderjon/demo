#
# Find FreeImage
#
# Try to find FreeImage, The open source image loader.
# This module defines:
# - FREE_IMAGE_INCLUDE_DIRS
# - FREE_IMAGE_LIBRARIES
# - FREE_IMAGE_FOUND
#
# The following variables can be set as arguments for the module:
# - FREE_IMAGE_ROOT_DIR: Root directory of FreeImage
#

# Additional modules
include(FindPackageHandleStandardArgs)

if (WIN32)
    # Find include files
    find_path(
            FREE_IMAGE_INCLUDE_DIR
            NAMES FreeImage.h
            PATHS
            $ENV{PROGRAMFILES}/include
            ${FREE_IMAGE_ROOT_DIR}/include
            DOC "The directory where FreeImage.h resides"
    )

    # Find library files
    find_library(
            FREE_IMAGE_LIBRARY
            NAMES FreeImage
            PATHS
            $ENV{PROGRAMFILES}/lib
            ${FREE_IMAGE_ROOT_DIR}/lib
            DOC "The FreeImage library"
    )
else()
    # Find include files
    find_path(
            FREE_IMAGE_INCLUDE_DIR
            NAMES FreeImage.h
            PATHS
            /usr/include
            /usr/local/include
            /sw/include
            /opt/local/include
            ${FREE_IMAGE_ROOT_DIR}/include
            DOC "The directory where FreeImage.h resides"
    )

    # Find library files
    # Try to use static libraries
    find_library(
            FREE_IMAGE_LIBRARY
            NAMES freeimage
            PATHS
            /usr/lib64
            /usr/lib
            /usr/lib/x86_64-linux-gnu
            /usr/local/lib64
            /usr/local/lib
            /sw/lib
            /opt/local/lib
            ${FREE_IMAGE_ROOT_DIR}/lib
            DOC "The FreeImage library"
    )
endif()

# Handle REQUIRED argument, define *_FOUND variable
find_package_handle_standard_args(
        FREE_IMAGE
        DEFAULT_MSG
        FREE_IMAGE_INCLUDE_DIR
        FREE_IMAGE_LIBRARY
)

# Define FREE_IMAGE_LIBRARIES and FREE_IMAGE_INCLUDE_DIRS
if (FREE_IMAGE_FOUND)
    set(FREE_IMAGE_LIBRARIES ${FREE_IMAGE_LIBRARY})
    set(FREE_IMAGE_INCLUDE_DIRS ${FREE_IMAGE_INCLUDE_DIR})
endif()

# Hide some variables
mark_as_advanced(FREE_IMAGE_INCLUDE_DIR FREE_IMAGE_LIBRARY)