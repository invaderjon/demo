// demo.cpp
#include "demo.h"

namespace demo
{

bool Demo::startup()
{
    return rndr::GrApi::init();
}

void Demo::run()
{
    _window.open();
    _window.activate();
    printf( "OpenGL version is (%s)\n", glGetString( GL_VERSION ) );

    glEnable( GL_DEPTH_TEST );
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );

    // run while the window is open
    while ( _window.isOpen() )
    {
        glfwPollEvents();

        _window.swapBuffer();
        _window.update();
    }
}

void Demo::shutdown()
{
    rndr::GrApi::terminate();
}

} // End nspc demo