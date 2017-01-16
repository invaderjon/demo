// itickable.h
//
// Interface definition of an object that is updated during the tick cycle.
//
#ifndef DEMO_ITICKABLE_H
#define DEMO_ITICKABLE_H

namespace demo
{

namespace obj
{

class ITickable
{
  public:
    // CONSTRUCTORS
    /**
     * Destruct the tickable.
     */
    virtual ~ITickable() = 0;

    // MEMBER FUNCTIONS
    /**
     * Prepare for the next tick cycle.
     */
    virtual void preTick() = 0;

    /**
     * Update the object.
     * @param dt The elapsed time in seconds.
     */
    virtual void tick( float dt ) = 0;

    /**
     * Clean up after the tick cycle.
     */
    virtual void postTick() = 0;
};

// CONSTRUCTORS
inline
ITickable::~ITickable()
{
}

} // End nspc obj

} // End nspc demo

#endif // DEMO_ITICKABLE_H
