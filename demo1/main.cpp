#include <iostream>

#include "demo/demo.h"
#include "demo/render/model.h"

int main()
{
    // run demo
    demo::Demo demo;
    demo.startup();
    demo.run();
    demo.shutdown();

    return 0;
}