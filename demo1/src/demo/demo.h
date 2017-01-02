// demo.h
//
// The central location that sets up the project.
//
#ifndef DEMO_DEMO_H
#define DEMO_DEMO_H

namespace demo
{

class Demo
{
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
    Demo( const Demo& other );

    /**
     * Destruct the demo.
     */
    ~Demo();

    // OPERATORS
    /**
     * Assign this as a copy of another demo.
     * @param other The other demo.
     * @return This.
     */
    Demo& operator=( const Demo& other );

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
Demo::Demo()
{
}

inline
Demo::Demo( const Demo& other )
{
    // TODO: copy over data
}

inline
Demo::~Demo()
{
}

// OPERATORS
inline
Demo& Demo::operator=( const Demo& other )
{
    // TODO: copy over data

    return *this;
}

} // End nspc demo

#endif // DEMO_DEMO_H
