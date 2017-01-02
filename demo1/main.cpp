#include <iostream>

#include "demo/demo.h"

int main()
{
    // create demo
    demo::Demo demo;

    // run demo
    demo.startup();
    demo.run();
    demo.shutdown();

    return 0;
}