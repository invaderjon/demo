// demo.h
//
// The central location that sets up the project.
//
#ifndef DEMO_DEMO_H
#define DEMO_DEMO_H

#include <demo/render/window.h>

namespace demo
{

class Demo
{
  private:
    // MEMBERS
    /**
     * The window the demo is running on.
     */
    rndr::Window _window;

    // HIDDEN FUNCTIONS
    /**
     * Hidden constructor.
     */
    Demo( const Demo& other ) = delete;

    /**
     * Hidden operator.
     */
    Demo& operator=( const Demo& other ) = delete;

  public:
    // CONSTRUCTORS
    /**
     * Construct a new demo.
     */
    Demo();

    /**
     * Construct a copy of the other demo.
     * @param other The other demo.
     */

    /**
     * Destruct the demo.
     */
    ~Demo();

    // MEMBER FUNCTIONS
    /**
     * Prepare the demo.
     * @return Whether it starts up successfully.
     */
    bool startup();

    /**
     * Run the demo.
     */
    void run();

    /**
     * Check if the demo is still running.
     * @return Is it still running?
     */
    bool isRunning() const;

    /**
     * Close and release the demo.
     */
    void shutdown();
};

// CONSTRUCTORS
inline
Demo::Demo() : _window()
{
}

inline
Demo::~Demo()
{
}

// MEMBER FUNCTIONS
inline
bool Demo::isRunning() const
{
    return _window.isOpen();
}

} // End nspc demo

#endif // DEMO_DEMO_H
