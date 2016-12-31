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

if (WIN32)
        find_package(GLEW REQUIRED)
endif()

# Includes
include_directories(
        ${OPENGL_INCLUDE_DIR}
        ${GLEW_INCLUDE_DIRS}
        ${GLFW_INCLUDE_DIRS}
        src
)

# Sources
set(
        SOURCE_FILES
        # root
        main.cpp
        # src/demo
        src/demo/demo.cpp
        src/demo/demo.h
        src/demo/intdef.cpp
        src/demo/intdef.h
        src/demo/port.cpp
        src/demo/port.h
        src/demo/strdef.cpp
        src/demo/strdef.h
        # src/demo/container
        src/demo/container/dynamic_array.cpp
        src/demo/container/dynamic_array.h
        src/demo/container/fixed_array.cpp
        src/demo/container/fixed_array.h
        src/demo/container/list.cpp
        src/demo/container/list.h
        src/demo/container/map.cpp
        src/demo/container/map.h
        src/demo/container/set.cpp
        src/demo/container/set.h
        # src/demo/memory
        src/demo/memory/allocator_guard.cpp
        src/demo/memory/allocator_guard.h
        src/demo/memory/counting_allocator.cpp
        src/demo/memory/counting_allocator.h
        src/demo/memory/default_allocator.cpp
        src/demo/memory/default_allocator.h
        src/demo/memory/iallocator.cpp
        src/demo/memory/iallocator.h
        src/demo/memory/memory_utils.cpp
        src/demo/memory/memory_utils.h
        src/demo/memory/stack_guard.cpp
        src/demo/memory/stack_guard.h
        # src/demo/objecct
        src/demo/object/camera.cpp
        src/demo/object/camera.h
        src/demo/object/itickable.cpp
        src/demo/object/itickable.h
        src/demo/object/object.cpp
        src/demo/object/object.h
        src/demo/object/scene.cpp
        src/demo/object/scene.h
        src/demo/object/transform.cpp
        src/demo/object/transform.h
        # src/demo/render
        src/demo/render/grapi.cpp
        src/demo/render/grapi.h
        src/demo/render/irenderable.cpp
        src/demo/render/irenderable.h
        src/demo/render/irendertarget.cpp
        src/demo/render/irendertarget.h
        src/demo/render/renderer.cpp
        src/demo/render/renderer.h
        src/demo/render/shader.cpp
        src/demo/render/shader.h
        src/demo/render/window.cpp
        src/demo/render/window.h
        # src/demo/utility
        src/demo/utility/hasher.cpp
        src/demo/utility/hasher.h
        src/demo/utility/hash_utils.cpp
        src/demo/utility/hash_utils.h
)

# Build
add_executable(demo1 ${SOURCE_FILES})
target_link_libraries(demo1 ${OPENGL_gl_LIBRARY} ${GLEW_LIBRARIES} ${GLFW_LIBRARIES})
