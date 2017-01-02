// window.h
//
// A simple window that acts as the render target for a renderer.
//
#ifndef DEMO_WINDOW_H
#define DEMO_WINDOW_H

#include "demo/render/irendertarget.h"

namespace demo
{

namespace rndr
{

class Window : public IRenderTarget
{
  private:


  public:
    // CONSTRUCTORS
    /**
     * Destruct the window.
     */
    virtual ~Window() = 0;

    // MEMBER FUNCTIONS
    /**
     * Active as a render target.
     */
    virtual void activate() = 0;

    /**
     * Check if this is the active render target.
     * @return Is it active?
     */
    virtual bool isActive() = 0;
};

// CONSTRUCTORS
Window::~Window()
{
}

} // End nspc rndr

} // End nspc demo

#endif // DEMO_WINDOW_H
