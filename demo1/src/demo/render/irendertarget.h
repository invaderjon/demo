// irendertarget.h
//
// Interface definition of a target that a renderer can use to draw to.
//
#ifndef DEMO_IRENDER_TARGET_H
#define DEMO_IRENDER_TARGET_H

namespace demo
{

namespace rndr
{

class IRenderTarget
{
  public:
    // CONSTRUCTORS
    /**
     * Destruct the render target.
     */
    virtual ~IRenderTarget() = 0;

    // MEMBER FUNCTIONS
    /**
     * Activate the render target.
     */
    virtual void activate() = 0;

    /**
     * Check if this is the active render target.
     * @return Is it active?
     */
    virtual bool isActive() const = 0;
};

// CONSTRUCTORS
inline
IRenderTarget::~IRenderTarget()
{
}

} // End nspc rndr

} // End nspc demo

#endif // DEMO_IRENDER_TARGET_H
