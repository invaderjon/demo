cmake_minimum_required(VERSION 3.0)
project(demo)

# Custom cmake search path
set(
        CMAKE_MODULE_PATH
        ${CMAKE_SOURCE_DIR}/cmake_modules
        ${CMAKE_MODULE_PATH}
)

#add_subdirectory(demo1)
add_subdirectory(demo2)