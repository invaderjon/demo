#include <iostream>

#include "demo/demo.h"

int main()
{
    using namespace demo;
    // create demo
    Demo demo;

    // run demo
    demo.startup();
    demo.run();
    demo.shutdown();

    return 0;
}