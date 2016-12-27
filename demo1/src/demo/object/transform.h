//
// Object transformation matrix.
//
#ifndef DEMO_TRANSFORM_H
#define DEMO_TRANSFORM_H

namespace demo
{

namespace obj
{

class Transform
{
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
     * Get the position.
     * @return The position.
     */
    const glm::vec3& position() const;

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
};

} // End nspc obj

} // End nspc demo

#endif // DEMO_TRANSFORM_H
