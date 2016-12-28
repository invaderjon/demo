// scene.h
//
// Manages a set of objects in a scene that can be interacted with and
// rendered.
//
#ifndef DEMO_SCENE_H
#define DEMO_SCENE_H

#include "demo/container/dynamic_array.h"
#include "demo/object/object.h"

namespace demo
{

namespace obj
{

class Scene
{
  private:
    // MEMBERS
    /**
     * The objects in the scene.
     */
    cntr::DynamicArray<Object*> _objects;

  public:
    // CONSTRUCTORS
    /**
     * Construct an empty scene.
     */
    Scene();

    /**
     * Construct a copy of another scene.
     * @param other The other scene.
     */
    Scene( const Scene& other );

    /**
     * Destruct the scene.
     */
    ~Scene();

    // OPERATORS
    /**
     * Assign this as a copy of another scene.
     * @param other The other scene.
     * @return This.
     */
    Scene& operator=( const Scene& other );

    // MEMBER FUNCTIONS
    /**
     * Add an object.
     * @param object The object.
     */
    void addObject( Object* object );

    /**
     * Remove an object.
     * @param object The object.
     */
    void removeObject( Object* object );

    /**
     * Get the objects in the scene.
     * @return The objects in the scene.
     */
    const cntr::DynamicArray<Object*>& getObjects() const;
};

// CONSTRUCTORS
inline
Scene::Scene() : _objects()
{
}

inline
Scene::Scene( const Scene& other ) : _objects( other._objects )
{
}

inline
Scene::~Scene()
{
}

// OPERATORS
inline
Scene& Scene::operator=( const Scene& other )
{
    _objects = other._objects;
    return *this;
}

// MEMBER FUNCTIONS
inline
void Scene::addObject( Object* object )
{
    _objects.push( object );
}

inline
void Scene::removeObject( Object* object )
{
    _objects.remove( object );
}

inline
const cntr::DynamicArray<Object *>& Scene::getObjects() const
{
    return _objects;
}

} // End nspc obj

} // End nspc demo

#endif // DEMO_SCENE_H
