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
}

} // End nspc rndr

} // End nspc demo
