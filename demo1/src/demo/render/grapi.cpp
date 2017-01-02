// grapi.cpp
#include "grapi.h"

namespace demo
{

namespace rndr
{

// UTILITY FUNCTIONS
bool GrApi::init()
{
    #ifdef _GLEW_
    glewInit();
    #endif

    return glfwInit() != 0;
}

void GrApi::terminate()
{
    glfwTerminate();
}

} // End nspc rndr

} // End nspc demo