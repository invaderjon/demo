cmake_minimum_required(VERSION 3.6)
project(demo1)

# Custom CMake search path
message(STATUS ${CMAKE_SOURCE_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/../cmake_modules ${CMAKE_MODULE_PATH})

# CMake variables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# External pacakges
find_package(OpenGL REQUIRED)
find_package(GLM REQUIRED)
find_package(GLFW REQUIRED)

# Includes
include_directories(${OPENGL_INCLUDE_DIR} ${GLFW_INCLUDE_DIRS})

# Sources
set(SOURCE_FILES main.cpp src/camera.cpp src/camera.h)

# Build
add_executable(demo1 ${SOURCE_FILES})
target_link_libraries(demo1 ${OPENGL_gl_LIBRARY} ${GLFW_LIBRARIES})
