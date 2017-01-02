// object.h
//
// An object that can be placed in the world and interact with it.
//
#ifndef DEMO_OBJECT_H
#define DEMO_OBJECT_H

#include "demo/intdef.h"
#include "demo/object/itickable.h"
#include "demo/object/transform.h"
#include "demo/strdef.h"

namespace demo
{

namespace obj
{

class Object : public ITickable
{
  private:
    // GLOBALS
    /**
     * The next id.
     */
    static uint64 g_nextId;

    // MEMBERS
    /**
     * The transform.
     */
    Transform _transform;

    /**
     * The tag.
     */
    String _tag;

    /**
     * The unique id.
     */
    uint64 _id;

    /**
     * Whether this is enabled.
     * This is true by default.
     */
    bool _isEnabled;

  public:
    // CONSTRUCTORS
    /**
     * Construct a new object.
     */
    Object();

    /**
     * Construct a copy of another object.
     * @param other The other object.
     */
    Object( const Object& other );

    /**
     * Destruct the object.
     */
    virtual ~Object();

    // OPERATORS
    /**
     * Assign this as a copy of another object.
     * @param other The other object.
     * @return This.
     */
    Object& operator=( const Object& other );

    // ACCESSOR FUNCTIONS
    /**
     * Get the transform.
     * @return The transform.
     */
    const Transform& transform() const;

    /**
     * Get the transform.
     * @return The transform.
     */
    Transform& transform();

    /**
     * Get the tag.
     * @return tag The tag.
     */
    const String& tag() const;

    /**
     * Get the unique object id.
     */
    uint64 id() const;

    /**
     * Check if the object is renderable.
     * @return Is it renderable?
     */
    virtual bool isRenderable() const;

    /**
     * Check if the object is enabled.
     * @return Is it enabled?
     */
    bool isEnabled() const;

    // MUTATOR FUNCTIONS
    /**
     * Set the transform.
     * @param transform The transform.
     */
    void setTransform( const Transform& transform );

    /**
     * Set the tag.
     * @param tag The tag.
     */
    void setTag( const String& tag );

    /**
     * Set whether this is enabled.
     * @param enabled Should be enabled?
     */
    void setEnabled( bool enabled );

    // MEMBER FUNCTIONS
    /**
     * Prepare for the next tick cycle.
     */
    virtual void preTick();

    /**
     * Update the object.
     * @param dt The elapsed time in seconds.
     */
    virtual void tick( float dt );

    /**
     * Clean up after the tick cycle.
     */
    virtual void postTick();

    /**
     * Render the object.
     */
    virtual void render();
};

// CONSTRUCTORS
inline
Object::Object() : _transform(), _tag(), _id( ++g_nextId ), _isEnabled( true )
{
}

inline
Object::Object( const Object& other ) 
    : _transform(), _tag( other._tag ), _id( other._id ), _isEnabled( true )
{
}

inline
Object::~Object()
{
}

// OPERATORS
inline
Object& Object::operator=( const Object& other )
{
    _transform = other._transform;
    _id = other._id;
    _isEnabled = other._isEnabled;
    return *this;
}

// ACCESSOR FUNCTIONS
inline
const Transform& Object::transform() const
{
    return _transform;
}

inline
Transform& Object::transform()
{
    return _transform;
}

inline
const String& Object::tag() const
{
    return _tag;
}

inline
uint64 Object::id() const
{
    return _id;
}

inline
bool Object::isRenderable() const
{
    return false;
}

inline
bool Object::isEnabled() const
{
    return _isEnabled;
}

// MUTATOR FUNCTIONS
inline
void Object::setTransform( const Transform& transform )
{
    _transform = transform;
}

inline
void Object::setTag( const String& tag )
{
    _tag = tag;
}

inline
void Object::setEnabled( bool enabled )
{
    _isEnabled = true;
}

// MEMBER FUNCTIONS
inline
void Object::preTick()
{
}

inline
void Object::tick( float dt )
{
}

inline
void Object::postTick()
{
}

inline
void Object::render()
{
}

} // End nspc obj

} // End nspc demo

#endif // DEMO_OBJECT_H
