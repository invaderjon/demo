// demo.h
//
// The central location that sets up the project.
//
#ifndef DEMO_DEMO_H
#define DEMO_DEMO_H

#include "demo/object/model_object.h"
#include "demo/object/camera.h"
#include "demo/object/scene.h"
#include "demo/render/grapi.h"
#include "demo/render/renderer.h"
#include "demo/render/shader.h"
#include "demo/render/window.h"
#include "demo/utility/clock.h"

namespace demo
{

class Demo
{
  private:
    // MEMBERS
    /**
     * The renderer.
     */
    rndr::Renderer _renderer;

    /**
     * The shader.
     */
    rndr::Shader _shader;

    /**
     * The window the demo is running on.
     */
    rndr::Window _window;

    /**
     * The camera.
     */
    obj::Camera _camera;

    /**
     * The model.
     */
    obj::ModelObject _model;

    /**
     * The scene.
     */
    obj::Scene _scene;

    /**
     * The game-time clock.
     * This affects the world and levels.
     */
    util::Clock _gameClock;

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
Demo::Demo() : _renderer(), _shader(), _window(), _camera(), _scene(),
               _gameClock()
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
