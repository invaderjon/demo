// rendertarget.h
//
// Abstract base class definition of a target that a renderer can draw to.
//
#ifndef DEMO_RENDER_TARGET_H
#define DEMO_RENDER_TARGET_H

#include "demo/intdef.h"

namespace demo
{

namespace rndr
{

class RenderTarget
{
  private:
    // GLOBALS
    /**
     * The next target id
     */
    static uint64 g_nextId;

    /**
     * The active target's id.
     */
    static uint64 g_activeId;

    // MEMBERS
    /**
     * The render target's unique id.
     */
    uint64 _id;

  protected:
    // ABSTRACT FUNCTIONS
    /**
     * Internally activates the render target.
     */
    virtual void activateTarget() = 0;

  public:
    // CONSTRUCTORS
    /**
     * Construct a render target.
     */
    RenderTarget();

    /**
     * Construct a copy of a render target.
     * @param other The other render target.
     */
    RenderTarget( const RenderTarget& other );

    /**
     * Destruct the render target.
     */
    virtual ~RenderTarget();

    // OPERATORS
    /**
     * Assign this as a copy of another rander target.
     * @param other The other render target.
     * @return This.
     */
    RenderTarget& operator=( const RenderTarget& other );

    // ACCESSOR FUNCTIONS
    /**
     * Get the target width.
     * @return The width.
     */
    virtual int32 width() const = 0;

    /**
     * Get the target height.
     * @return The height.
     */
    virtual int32 height() const = 0;

    /**
     * Get the target aspect ratio.
     * @return The aspect ratio.
     */
    virtual float aspectRatio() const = 0;

    // MEMBER FUNCTIONS
    /**
     * Activate the render target.
     */
    void activate();

    /**
     * Check if this is the active render target.
     * @return Is it active?
     */
    bool isActive() const;
};

// CONSTRUCTORS
inline
RenderTarget::RenderTarget() : _id( ++g_nextId )
{
}

inline
RenderTarget::RenderTarget( const RenderTarget& other ) : _id( other._id )
{
}

inline
RenderTarget::~RenderTarget()
{
}

// OPERATORS
inline
RenderTarget& RenderTarget::operator=( const RenderTarget& other )
{
    _id = other._id;
    return *this;
}

// MEMBER FUNCTIONS
inline
void RenderTarget::activate()
{
    activateTarget();
    g_activeId = _id;
}

inline
bool RenderTarget::isActive() const
{
    return g_activeId == _id;
}

} // End nspc rndr

} // End nspc demo

#endif // DEMO_RENDER_TARGET_H
