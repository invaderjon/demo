// transform.h
//
// Object transformation matrix.
//
// The default transform is centered at the origin and its look direction is in
// the positive z-axis direction.
//
// The transformations are applied in the following order:
// scale
// rotation
// translation
//
// Rotating about a point affects both scale and rotation.
// Changing the rotation directly will not effect position.
//
#ifndef DEMO_TRANSFORM_H
#define DEMO_TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace demo
{

namespace obj
{

class Transform
{
  private:
    // MEMBERS
    /**
     * The transformation matrix.
     */
    glm::mat4 _matrix;

    /**
     * The rotation.
     */
    glm::quat _rotation;

    /**
     * The position.
     */
    glm::vec3 _position;

    /**
     * The scale.
     */
    float _scale;

    /**
     * Whether or not the transform has changed.
     */
    bool _hasChanged;

    // HELPER FUNCTIONS
    /**
     * Recompute the transformation matrix.
     */
    void recomputeMatrix();

  public:
    // CONSTRUCTORS
    /**
     * Construct a new transform.
     */
    Transform();

    /**
     * Construct a new transform.
     */
    Transform( const Transform& other );

    /**
     * Destruct the transformation matrix.
     */
    ~Transform();

    // OPERATORS
    /**
     * Assign this as a copy of another transform.
     * @param other The other transform.
     * @return This.
     */
    Transform& operator=( const Transform& other );

    // ACCESSOR FUNCTIONS
    /**
     * Get the transformation matrix.
     * @return The matrix.
     */
    const glm::mat4& matrix() const;

    /**
     * Get the position.
     * @return The position.
     */
    const glm::vec3& position() const;

    /**
     * Get the rotation.
     * @return The rotation.
     */
    const glm::quat& rotation() const;

    /**
     * Get the euler rotation angles.
     *
     * This is pitch, roll, and yaw in that order.
     * @return The euler rotation.
     */
    glm::vec3 eulerRotation() const;

    /**
     * Get the forward vector.
     * @return The unit directional vector.
     */
    glm::vec3 forward() const;

    /**
     * Get the up vector.
     * @return The unit directional vector.
     */
    glm::vec3 up() const;

    /**
     * Get the right vector.
     * @return The unit directional vector.
     */
    glm::vec3 right() const;

    /**
     * Get the scale.
     * @return The scale.
     */
    float scale() const;

    /**
     * Check if the transform has changed since the flag was last reset.
     * @return Has it changed?
     */
    bool hasChanged() const;

    // MUTATOR FUNCTIONS
    /**
     * Set the position.
     * @param position The position.
     */
    void setPosition( const glm::vec3& position );

    /**
     * Set the rotation.
     * @param rotation The rotation.
     */
    void setRotation( const glm::quat& rotation );

    /**
     * Set the rotation around the z axis, x axis, and then y axis in that
     * order.
     * @param x The pitch in degrees.
     * @param y The roll in degrees.
     * @param z The yaw in degrees.
     */
    void setEulerRotation( float x, float y, float z );

    /**
     * Sets the rotation around the z axis, x axis, and then y axis in that
     * order.
     * @param rotation The pitch, roll, and yaw in degrees.
     */
    void setEulerRotation( const glm::vec3& rotation );

    /**
     * Set the scale.
     * @param scale The scale.
     */
    void setScale( float scale );

    // MEMBER FUNCTIONS
    /**
     * Translate the transform.
     * @param translation The translation.
     */
    void translate( const glm::vec3& translation );

    /**
     * Rotate the transform around its center point.
     * @param rotation The rotation.
     */
    void rotate( const glm::quat& rotation );

    /**
     * Rotate around the z axis, x axis, and then y axis in that order.
      * @param x The pitch in degrees.
      * @param y The roll in degrees.
      * @param z The yaw in degrees.
      */
    void rotateEuler( float x, float y, float z );

    /**
     * Rotate around the z axis, x axis, and then y axis in that order.
     * @param rotation The pitch, roll, and yaw in degrees.
     */
    void rotateEuler( const glm::vec3& rotation );

    /**
     * Rotate the transform about the specified point and axis.
     * @param point The point.
     * @param rotation The rotation to apply.
     */
    void rotateAround( const glm::vec3& point, const glm::quat& rotation );

    /**
     * Scale the transform.
     *
     * This does not effect translation.
     *
     * @param scale Scale the transform.
     */
    void scale( float scale );

    /**
     * Reset the hasChanged flag.
     */
    void resetChangedFlag();
};

// CONSTRUCTORS
inline
Transform::Transform() : _matrix(), _position(), _scale( 1.0f ), _rotation(),
                         _hasChanged()
{
}

inline
Transform::Transform( const Transform& other )
    : _matrix( other._matrix ), _position( other._position ),
      _scale( other._scale ), _rotation( other._rotation ),
      _hasChanged( other._hasChanged )
{
}

inline
Transform::~Transform()
{
}

// OPERATORS
inline
Transform& Transform::operator=( const Transform& other )
{
    _matrix = other._matrix;
    _position = other._position;
    _rotation = other._rotation;
    _scale = other._scale;
    _hasChanged = other._hasChanged;

    return *this;
}

// ACCESSOR FUNCTIONS
inline
const glm::mat4& Transform::matrix() const
{
    return _matrix;
}

inline
const glm::vec3& Transform::position() const
{
    return _position;
}

inline
const glm::quat& Transform::rotation() const
{
    return _rotation;
}

inline
glm::vec3 Transform::eulerRotation() const
{
    return glm::eulerAngles( _rotation );
}

inline
glm::vec3 Transform::forward() const
{
    glm::vec4 dir = _rotation * glm::vec4( 0.0f, 0.0f, 1.0f, 1.0f );
    return glm::normalize( glm::vec3( dir ) );
}

inline
glm::vec3 Transform::up() const
{
    glm::vec4 dir = _rotation * glm::vec4( 0.0f, 1.0f, 0.0f, 1.0f );
    return glm::normalize( glm::vec3( dir ) );
}

inline
glm::vec3 Transform::right() const
{
    glm::vec4 dir = _rotation * glm::vec4( 1.0f, 0.0f, 0.0f, 1.0f );
    return glm::normalize( glm::vec3( dir ) );
}

inline
float Transform::scale() const
{
    return _scale;
}

inline
bool Transform::hasChanged() const
{
    return _hasChanged;
}

// MUTATOR FUNCTIONS
inline
void Transform::setPosition( const glm::vec3& position )
{
    _position = position;
    recomputeMatrix();
}

inline
void Transform::setRotation( const glm::quat& rotation )
{
    _rotation = rotation;
    recomputeMatrix();
}

inline
void Transform::setEulerRotation( float x, float y, float z )
{
    setEulerRotation( glm::vec3( x, y, z ) );
}

inline
void Transform::setScale( float scale )
{
    _scale = scale;
    recomputeMatrix();
}

// MEMBER FUNCTIONS
inline
void Transform::translate( const glm::vec3& translation )
{
    _position += translation;
    recomputeMatrix();
}

inline
void Transform::rotate( const glm::quat& rotation )
{
    _rotation *= rotation;
    recomputeMatrix();
}

inline
void Transform::rotateEuler( float x, float y, float z )
{
    rotateEuler( glm::vec3( x, y, z ) );
}

inline
void Transform::scale( float scale )
{
    _scale *= scale;
    recomputeMatrix();
}

inline
void Transform::resetChangedFlag()
{
    _hasChanged = false;
}

} // End nspc obj

} // End nspc demo

#endif // DEMO_TRANSFORM_H
