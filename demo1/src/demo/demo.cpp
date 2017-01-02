// demo.cpp
#include "demo.h"

#include <iostream>

#include "demo/render/grapi.h"

namespace demo
{

bool Demo::startup()
{
    // initialize graphics
    if ( !rndr::GrApi::init() )
    {
        return false;
    }

    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 1 );
    GLFWwindow* win = glfwCreateWindow( 300, 400, "test", nullptr, nullptr );
    glfwMakeContextCurrent( win );

    // display opengl version
    printf( "OpenGL version is (%s)\n", glGetString( GL_VERSION ) );

    rndr::GrApi::terminate();
    return 0;
}

void Demo::run()
{
}

bool Demo::isRunning() const
{
}

void Demo::shutdown()
{
    rndr::GrApi::terminate();
}

} // End nspc demo