cmake_minimum_required(VERSION 3.6)
project(demo1)

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
set(
        SOURCE_FILES
        # root
        main.cpp
        # src/demo
        src/demo/demo.cpp
        src/demo/demo.h
        # src/demo
        src/demo/object/camera.cpp
        src/demo/object/camera.h
        # src/demo/object
        src/demo/object/itickable.cpp
        src/demo/object/itickable.h
        src/demo/object/object.cpp
        src/demo/object/object.h
        src/demo/object/transform.cpp
        src/demo/object/transform.h
        # src/demo/render
        src/demo/render/irendertarget.cpp
        src/demo/render/irendertarget.h
        src/demo/render/renderer.cpp
        src/demo/render/renderer.h
        src/demo/render/window.cpp
        src/demo/render/window.h
)

# Build
add_executable(demo1 ${SOURCE_FILES})
target_link_libraries(demo1 ${OPENGL_gl_LIBRARY} ${GLFW_LIBRARIES})
