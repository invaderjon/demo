// grapi.cpp
#include "grapi.h"

namespace demo
{

namespace rndr
{

// UTILITY FUNCTIONS
void GrApi::init()
{
    #ifdef _GLEW_
    glewInit();
    #endif

    glfwInit();
}

void GrApi::terminate()
{
    glfwTerminate();
}

} // End nspc rndr

} // End nspc demo