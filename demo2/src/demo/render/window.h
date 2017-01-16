// window.h
//
// A simple window that acts as the render target for a renderer.
//
#ifndef DEMO_WINDOW_H
#define DEMO_WINDOW_H

#include "demo/render/grapi.h"
#include "demo/render/rendertarget.h"
#include "demo/strdef.h"

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

    /**
     * The window title.
     */
    String _title;

    /**
     * The width.
     */
    int32 _width;

    /**
     * The height.
     */
    int32 _height;

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
    void activateTarget() override;

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

    // ACCESSOR FUNCTIONS
    /**
     * Get the title.
     * @return The title.
     */
    const String& title() const;

    /**
     * Get the width.
     * @return The width.
     */
    int32 width() const override;

    /**
     * Get the height.
     * @return The height.
     */
    int32 height() const override;

    /**
     * Get the aspect ratio.
     * @return The aspect ratio.
     */
    float aspectRatio() const override;

    // MUTATOR FUNCTIONS
    /**
     * Set the title.
     * @param title The title.
     */
    void setTitle( const String& title );

    /**
     * Set the width.
     * @param width The width.
     */
    void setWidth( int32 width );

    /**
     * Set the height.
     * @param height The height.
     */
    void setHeight( int32 height );

    /**
     * Set the size.
     * @param width The width.
     * @param height The height.
     */
    void setSize( int32 width, int32 height );

    // MEMBER FUNCTIONS
    /**
     * Open the window.
     * This does nothing if the window is already open.
     */
    void open();

    /**
     * Poll for window events.
     * This does nothing if the window is not open.
     */
    void update();

    /**
     * Swap the buffer.
     */
    void swapBuffer();

    /**
     * Close the window.
     * This does nothing if the window is not open.
     * The size will be invalid after the window is closed.
     */
    void close();

    /**
     * Check if the window is visible and open.
     * @return Is it open?
     */
    bool isOpen() const;
};

// CONSTRUCTORS
inline
Window::Window() : _window( nullptr ), _width( 800 ), _height( 600 )
{
}

inline
Window::~Window()
{
    if ( _window != nullptr )
    {
        glfwDestroyWindow( _window );
    }
}

// ACCESSOR FUNCTIONS
inline
const String& Window::title() const
{
    return _title;
}

inline
int32 Window::width() const
{
    return _width;
}

inline
int32 Window::height() const
{
    return _height;
}

inline
float Window::aspectRatio() const
{
    return static_cast<float>( width() ) /
            static_cast<float>( height() );
}

// MUTATOR FUNCTIONS
inline
void Window::setTitle( const String& title )
{
    if ( isOpen() )
    {
        glfwSetWindowTitle( _window, title.c_str() );
    }

    _title = title;
}

inline
void Window::setHeight( int32 height )
{
    if ( isOpen() )
    {
        glfwSetWindowSize( _window, _width, height );
    }

    _height = height;
}

inline
void Window::setWidth( int32 width )
{
    if ( isOpen() )
    {
        glfwSetWindowSize( _window, width, _height );
    }

    _width = width;
}

inline
void Window::setSize( int32 width, int32 height )
{
    if ( isOpen() )
    {
        glfwSetWindowSize( _window, width, height );
    }

    _width = width;
    _height = height;
}

// MEMBER FUNCTIONS
inline
void Window::swapBuffer()
{
    if ( isOpen() )
    {
        glfwSwapBuffers( _window );
    }
}

inline
bool Window::isOpen() const
{
    return _window != nullptr;
}

} // End nspc rndr

} // End nspc demo

#endif // DEMO_WINDOW_H
