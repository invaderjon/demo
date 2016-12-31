#include <iostream>

#include "demo/render/grapi.h"
#include "demo/render/shader.h"

#define GLFW_DLL 
#include <GLFW/glfw3.h>

int main()
{
    using namespace demo;

    glfwInit();
    GLFWwindow* win = glfwCreateWindow( 300, 400, "test", nullptr, nullptr );;

    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        std::cout << "Failed to load glew" << err << std::endl;
        return -1;
    }
    rndr::Shader test( "test1" );
    test.load();
    std::cout << "Hello, World!" << std::endl;

    glfwTerminate();
    return 0;
}