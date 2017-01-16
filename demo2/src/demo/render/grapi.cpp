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
bool GrApi::init()
{
    return glfwInit() != 0;
}

void GrApi::terminate()
{
    glfwTerminate();
}

} // End nspc rndr

} // End nspc demo