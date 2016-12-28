// renderer.h
//
// Draws scenes as they are observed by a specified camera.
//
// The renderer requires a render target which specifies where to draw the
// scene to. This can be a window or it can be a portion of one such as in
// the case of a split screen.
//
#ifndef DEMO_RENDERER_H
#define DEMO_RENDERER_H

#include "demo/object/camera.h"

namespace demo
{

namespace rndr
{

class Renderer
{
  public:
    // CONSTRUCTORS
    /**
     * Construct a new renderer.
     */
    Renderer();

    /**
     * Construct a copy of a renderer.
     * @param other The other renderer.
     */
    Renderer( const Renderer& other );

    /**
     * Destruct the renderer.
     */
    ~Renderer();

    // OPERATORS
    /**
     * Assign this as a copy of a renderer.
     * @param other The other renderer.
     * @return This.
     */
    Renderer& operator=( const Renderer& other );

    // MEMBER FUNCTIONS
    /**
     * Render the specified scene from the viewpoint of the specified camera.
     * @param camera The camera
     */
    void render( const obj::Camera& camera );
};

} // End nspc rndr

} // End nspc demo

#endif // DEMO_RENDERER_H
