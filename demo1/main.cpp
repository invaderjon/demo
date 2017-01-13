#include <iostream>

#include "demo/demo.h"
#include "demo/render/model.h"

int main()
{
    // test load model
    demo::rndr::Model cube( "res/models/cube.obj" );

    // run demo
    demo::Demo demo;
    demo.startup();
    demo.run();
    demo.shutdown();

    return 0;
}