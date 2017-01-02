// camera.h
//
// A camera that can be used to render a scene.
//
#ifndef DEMO_CAMERA_H
#define DEMO_CAMERA_H

#include "demo/object/object.h"

namespace demo
{

namespace obj
{

class Camera : public Object
{
  private:
    // MEMBERS
    /**
     * The field of view.
     */
    float _fieldOfView;

    /**
     * The near plane distance.
     */
    float _nearPlane;

    /**
     * The far plane distance.
     */
    float _farPlane;

  public:
    // CONSTRUCTORS
    /**
     * Construct a basic camera.
     */
    Camera();

    /**
     * Construct a copy of a camera.
     * @param other The other camera.
     */
    Camera( const Camera& other );

    /**
     * Destruct the camera.
     */
    virtual ~Camera();

    // OPERATORS
    /**
     * Assign this as a copy of another camera.
     * @param other The other camera.
     * @return This.
     */
    Camera& operator=( const Camera& other );

    // ACCESSOR FUNCTIONS
    /**
     * Get the field of view in degrees.
     * @return The field of view.
     */
    float fieldOfView() const;

    /**
     * The near clipping plane distance.
     * @return The near plane distance.
     */
    float nearPlane() const;

    /**
     * The far clipping plane distance.
     * @return
     */
    float farPlane() const;

    // MUTATOR FUNCTIONS
    /**
     * Set the field of view.
     * @param fieldOfView The field of view.
     */
    void setFieldOfView( float fieldOfView );

    /**
     * Set the near plane distance.
     * @param distance The distance.
     */
    void setNearPlane( float distance );

    /**
     * Set the far plane distance.
     * @param distance The distance.
     */
    void setFarPlane( float distance );
};

// CONSTRUCTORS
inline
Camera::Camera() : _fieldOfView(), _nearPlane(), _farPlane()
{
}

inline
Camera::Camera( const Camera& other )
        : _fieldOfView( other._fieldOfView ), _nearPlane( other._nearPlane ),
          _farPlane( other._farPlane )
{
}

inline
Camera::~Camera()
{
}

// ACCESSOR FUNCTIONS
inline
float Camera::fieldOfView() const
{
    return _fieldOfView;
}

inline
float Camera::nearPlane() const
{
    return _nearPlane;
}

inline
float Camera::farPlane() const
{
    return _farPlane;
}

// MUTATOR FUNCTIONS
inline
void Camera::setFieldOfView( float fieldOfView )
{
    _fieldOfView = fieldOfView;
}

inline
void Camera::setNearPlane( float distance )
{
    _nearPlane = distance;
}

inline
void Camera::setFarPlane( float distance )
{
    _farPlane = distance;
}

} // End nspc obj

} // End nspc demo

#endif // DEMO_CAMERA_H
