// camera.h
//
// A camera that can be used to render a scene.
//
#ifndef DEMO_CAMERA_H
#define DEMO_CAMERA_H

namespace demo
{

namespace obj {

class Camera {
  private:


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
    ~Camera();

    // OPERATORS
    /**
     * Assign this as a copy of another camera.
     * @param other The other camera.
     * @return This.
     */
    Camera& operator=( const Camera& other );

    // ACCESSOR FUNCTIONS
    /**
     * Get the position.
     * @return The position.
     */
    void* position() const;

    /**
     * Get the forward/look direction.
     * @return The unit directional vector.
     */
    void* forward() const;

    /**
     * Get the viewing up direction.
     * @return The unit directional vector.
     */
    void* up() const;

    /**
     * Get the viewing right direction.
     * @return The unit directional vector.
     */
    void* right() const;

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
     * Set the position.
     * @param position
     */
    void setPosition( void* position );


};

} // End nspc obj

} // End nspc demo

#endif // DEMO_CAMERA_H
