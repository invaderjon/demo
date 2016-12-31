// demo.cpp
#include "demo.h"

#include "demo/render/grapi.h"

namespace demo
{

void Demo::startup()
{
    // initialize the components
    GrApi::init();
}

void Demo::run()
{
}

bool Demo::isRunning() const
{
}

void Demo::shutdown()
{
}

} // End nspc demo