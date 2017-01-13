// irenderable.h
//
// Interface definition of an object that can be rendered.
//
#ifndef DEMO_IRENDERABLE_H
#define DEMO_IRENDERABLE_H

#include "demo/render/shader.h"

namespace demo
{

namespace rndr
{

class IRenderable
{
  public:
    // CONSTRUCTORS
    /**
     * Destruct the renderable.
     */
    virtual ~IRenderable() = 0;

    // MEMBER FUNCTIONS
    /**
     * Render the object.
      * @param shader The shader to use during rendering.
     */
    virtual void render( const Shader& shader ) = 0;
};

// CONSTRUCTORS
inline
IRenderable::~IRenderable()
{
}

} // End nspc rndr

} // End nspc demo

#endif // DEMO_IRENDERABLE_H