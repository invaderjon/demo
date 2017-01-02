#include <iostream>

#include "demo/render/grapi.h"
#include "demo/render/shader.h"

int main()
{
    using namespace demo;
    rndr::GrApi::init();

    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 1 );
    GLFWwindow* win = glfwCreateWindow( 300, 400, "test", nullptr, nullptr );
    glfwMakeContextCurrent( win );

    printf( "OpenGL version is (%s)\n", glGetString( GL_VERSION ) );

    rndr::Shader test( "test1" );
    test.load();
    std::cout << "Hello, World!" << std::endl;

    rndr::GrApi::terminate();
    return 0;
}