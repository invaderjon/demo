// grapi.cpp
#include "grapi.h"

namespace demo
{

namespace rndr
{

void GrApi::init()
{
    #ifdef _GLEW_
    glewInit();
    #endif
}

} // End nspc rndr

} // End nspc demo