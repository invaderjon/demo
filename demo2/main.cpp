#include "demo/demo.h"

int main()
{
    // run demo
    demo::Demo demo;
    demo.startup();
    demo.run();
    demo.shutdown();

    return 0;
}