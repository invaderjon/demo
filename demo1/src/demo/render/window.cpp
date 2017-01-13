// window.cpp
#include "window.h"

namespace demo
{

namespace rndr
{

// ABSTRACT FUNCTIONS
void Window::activateTarget()
{
    glfwMakeContextCurrent( _window );
    glViewport( 0, 0, _width, _height );
}

// MEMBER FUNCTIONS
void Window::open()
{
    if ( isOpen() )
    {
        return;
    }

    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 1 );
    _window = glfwCreateWindow( _width, _height, _title.c_str(), nullptr,
                                nullptr );
}

void Window::update()
{
    if ( !isOpen() )
    {
        return;
    }

    glfwGetWindowSize( _window, &_width, &_height );

    // if the window should close then do so
    if ( glfwWindowShouldClose( _window ) )
    {
        glfwDestroyWindow( _window );
        _window = nullptr;
    }
}

void Window::close()
{
    if ( !isOpen() )
    {
        return;
    }

    glfwDestroyWindow( _window );
    _window = nullptr;
}

} // End nspc rndr

} // End nspc demo
