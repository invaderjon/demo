// irenderable.h
//
// Interface definition of an object that can be rendered.
//
#ifndef DEMO_IRENDERABLE_H
#define DEMO_IRENDERABLE_H

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
     */
    virtual void render() = 0;
};

// CONSTRUCTORS
inline
IRenderable::~IRenderable()
{
}

} // End nspc rndr

} // End nspc demo

#endif // DEMO_IRENDERABLE_H