// window.h
//
// A simple window that acts as the render target for a renderer.
//
#ifndef DEMO_WINDOW_H
#define DEMO_WINDOW_H

#include "demo/render/grapi.h"
#include "demo/render/rendertarget.h"

namespace demo
{

namespace rndr
{

class Window : public RenderTarget
{
  private:
    // MEMBERS
    /**
     * The window.
     */
    GLFWwindow* _window;

    // HIDDEN FUNCTIONS
    /**
     * Hidden constructor.
     */
    Window( const Window& other ) = delete;

    /**
     * Hidden operator.
     */
    Window& operator=( const Window& other ) = delete;

  protected:
    // ABSTRACT FUNCTIONS
    /**
     * Activate the render target.
     */
    virtual void activateTarget();

  public:
    // CONSTRUCTORS
    /**
     * Construct an empty window.
     */
    Window();

    /**
     * Destruct the window.
     */
    virtual ~Window();
};

// CONSTRUCTORS
inline
Window::Window() : _window( nullptr )
{
}

inline
Window::~Window()
{
}

} // End nspc rndr

} // End nspc demo

#endif // DEMO_WINDOW_H
