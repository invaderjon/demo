// grapi.cpp
#include "grapi.h"

#include <iostream>

#include "demo/intdef.h"
#include "demo/render/window.h"

namespace demo
{

namespace rndr
{

// UTILITY FUNCTIONS
bool GrApi::startup()
{
    return glfwInit() != 0;
}

void GrApi::shutdown()
{
    glfwTerminate();
}

void GrApi::logError( const String& tag )
{
    int32 error = glGetError();
    if ( error != GL_NO_ERROR )
    {
        std::cout << "GPU Error [" + tag + "]: " << error << std::endl;
    }
}

} // End nspc rndr

} // End nspc demo