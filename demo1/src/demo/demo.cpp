// demo.cpp
#include "demo.h"

#include <iostream>

#include "demo/render/grapi.h"
#include <GLFW/glfw3.h>

namespace demo
{

bool Demo::startup()
{
    // initialize the components
    rndr::GrApi::init();

    if ( !glfwInit() )
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return false;
    }
}

void Demo::run()
{
}

bool Demo::isRunning() const
{
}

void Demo::shutdown()
{
    // glfwTerminate();
}

} // End nspc demo