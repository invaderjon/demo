// transform.h
//
// Object transformation matrix.
//
// The default transform is centered at the origin and its look direction is in
// the negative z-axis direction and the up direction is in the positive y-axis.
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
    glm::vec3 _scale;

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
    // CONSTANTS
    /**
     * The forward directional vector.
     */
    const static glm::vec3 FORWARD;

    /**
     * The upward directional vector.
     */
    const static glm::vec3 UP;

    /**
     * The right direction vector.
     */
    const static glm::vec3 RIGHT;

    /**
     * The zero vector.
     */
    const static glm::vec3 ZERO;

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
     * Get the scale factor vector.
     * @return The scale factor vector.
     */
    const glm::vec3& scale() const;

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
     * Get the x-axis scale factor.
     * @return The scale factor.
     */
    float scaleX() const;

    /**
     * Get the y-axis scale factor.
     * @return The scale factor.
     */
    float scaleY() const;

    /**
     * Get the z-axis scale factor.
     * @return The scale factor.
     */
    float scaleZ() const;

    /**
     * Check if the transform has changed since the flag was last reset.
     * @return Has it changed?
     */
    bool hasChanged() const;

    // MUTATOR FUNCTIONS
    /**
     * Set the position.
     * @param x The x-coordinate.
     * @param y The y-coordinate.
     * @param z The z-coordinate.
     */
    void setPosition( float x, float y, float z );

    /**
     * Set the position.
     * @param position The position.
     */
    void setPosition( const glm::vec3& position );

    /**
     * Set the rotation.
     * @param x The quat x value.
     * @param y The quat y value.
     * @param z The quat z value.
     * @param r The quat r value.
     */
    void setRotation( float x, float y, float z, float r );

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
     * Set the scale factor.
     * This sets the x, y, and z scale factors.
     * @param scale The scale factor.
     */
    void setScale( float scale );

    /**
     * Set the scale factors.
     * @param xScale The x-axis scale factor.
     * @param yScale The y-axis scale factor.
     * @param zScale The z-axis scale factor.
     */
    void setScale( float xScale, float yScale, float zScale );

    /**
     * Set the scale factor vector.
     * @param scale The scale factor vector.
     */
    void setScale( const glm::vec3& scale );

    /**
     * Set the x-axis scale factor.
     * @param scale The scale factor.
     */
    void setScaleX( float scale );

    /**
     * Set the y-axis scale factor.
     * @param scale The scale factor.
     */
    void setScaleY( float scale );

    /**
     * Set the z-axis scale factor.
     * @param scale The scale factor.
     */
    void setScaleZ( float scale );

    // MEMBER FUNCTIONS
    /**
     * Translate the transform.
     * @param x The x-axis translation.
     * @param y The y-axis translation.
     * @param z The z-axis translation.
     */
    void translate( float x, float y, float z );

    /**
     * Translate the transform.
     * @param translation The translation.
     */
    void translate( const glm::vec3& translation );

    /**
     * Rotate the transform around its center point.
     * @param x The quat axis direction x value.
     * @param y The quat axis direction y value.
     * @param z The quat axis direction z value.
     * @param r The quat rotation.
     */
    void rotate( float x, float y, float z, float r );

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
     * @param scale The scale factor..
     */
    void scale( float scale );

    /**
     * Scale the transform on the x-axis.
     *
     * This does not effect translation.
     *
     * @param scale The scale factor.
     */
    void scaleX( float scale );

    /**
     * Scale the transform on the y-axis.
     *
     * This does not effect translation.
     *
     * @param scale The scale factor.
     */
    void scaleY( float scale );

    /**
     * Scale the transform on the z-axis.
     *
     * This does not effect translation.
     *
     * @param scale The scale factor.
     */
    void scaleZ( float scale );

    /**
     * Look at the specified location.
     * @param center The look target.
     */
    void lookAt( const glm::vec3& center );

    /**
     * Look at the specified location.
     * @param center The look target.
     * @param up The upward direction.
     */
    void lookAt( const glm::vec3& center,
                 const glm::vec3& up );

    /**
     * Look at the specified location.
     * @param eye The eye location.
     * @param center The center.
     * @param up The upward direction.
     */
    void lookAt( const glm::vec3& eye,
                 const glm::vec3& center,
                 const glm::vec3& up );

    /**
     * Reset the hasChanged flag.
     */
    void resetChangedFlag();
};

// CONSTRUCTORS
inline
Transform::Transform() : _matrix(), _position(), _scale( 1.0f, 1.0f, 1.0f ),
                         _rotation(), _hasChanged( true )
{
}

inline
Transform::Transform( const Transform& other )
    : _matrix( other._matrix ), _position( other._position ),
      _scale( other._scale ), _rotation( other._rotation ),
      _hasChanged( true )
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
    _hasChanged = true;

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
const glm::vec3& Transform::scale() const
{
    return _scale;
}

inline
glm::vec3 Transform::eulerRotation() const
{
    return glm::eulerAngles( _rotation );
}

inline
glm::vec3 Transform::forward() const
{
    glm::vec4 dir = _rotation * glm::vec4( FORWARD, 1.0f );
    return glm::normalize( glm::vec3( dir ) );
}

inline
glm::vec3 Transform::up() const
{
    glm::vec4 dir = _rotation * glm::vec4( UP, 1.0f );
    return glm::normalize( glm::vec3( dir ) );
}

inline
glm::vec3 Transform::right() const
{
    glm::vec4 dir = _rotation * glm::vec4( RIGHT, 1.0f );
    return glm::normalize( glm::vec3( dir ) );
}

inline
bool Transform::hasChanged() const
{
    return _hasChanged;
}

inline
float Transform::scaleX() const
{
    return _scale.x;
}

inline
float Transform::scaleY() const
{
    return _scale.y;
}

inline
float Transform::scaleZ() const
{
    return _scale.z;
}

// MUTATOR FUNCTIONS
inline
void Transform::setPosition( float x, float y, float z )
{
    setPosition( glm::vec3( x, y, z ) );
}

inline
void Transform::setPosition( const glm::vec3& position )
{
    _position = position;
    recomputeMatrix();
}

inline
void Transform::setRotation( float x, float y, float z, float r )
{
    setRotation( glm::quat( x, y, z, r ) );
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
    _scale = glm::vec3( scale, scale, scale );
    recomputeMatrix();
}

inline
void Transform::setScale( float xScale, float yScale, float zScale )
{
    setScale( glm::vec3( xScale, yScale, zScale ) );
}

inline
void Transform::setScale( const glm::vec3& scale )
{
    _scale = scale;
    recomputeMatrix();
}

inline
void Transform::setScaleX( float scale )
{
    _scale.x = scale;
    recomputeMatrix();
}

inline
void Transform::setScaleY( float scale )
{
    _scale.y = scale;
    recomputeMatrix();
}

inline
void Transform::setScaleZ( float scale )
{
    _scale.z = scale;
    recomputeMatrix();
}

// MEMBER FUNCTIONS
inline
void Transform::translate( float x, float y, float z )
{
    translate( glm::vec3( x, y, z ) );
}

inline
void Transform::translate( const glm::vec3& translation )
{
    _position += translation;
    recomputeMatrix();
}

inline
void Transform::rotate( float x, float y, float z, float r )
{
    rotate( glm::quat( x, y, z, r ) );
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
void Transform::scaleX( float scale )
{
    _scale.x *= scale;
}

inline
void Transform::scaleY( float scale )
{
    _scale.y *= scale;
}

inline
void Transform::scaleZ( float scale )
{
    _scale.z *= scale;
}

inline
void Transform::lookAt( const glm::vec3& center )
{
    lookAt( center, glm::vec3( 0, 1, 0 ) );
}

inline
void Transform::lookAt( const glm::vec3& center, const glm::vec3& up )
{
    lookAt( _position, center, up );
}

inline
void Transform::resetChangedFlag()
{
    _hasChanged = false;
}

} // End nspc obj

} // End nspc demo

#endif // DEMO_TRANSFORM_H
