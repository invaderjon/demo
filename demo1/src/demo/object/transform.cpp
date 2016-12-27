#include "transform.h"

namespace demo
{

namespace obj
{

// MUTATOR FUNCTIONS
void Transform::setEulerRotation( const glm::vec3& rotation )
{
    glm::quat yaw = glm::rotate( glm::quat(), rotation.z,
                                 glm::vec3( 0.0f, 0.0f, 1.0f ) );

    glm::quat pitch = glm::rotate( glm::quat(), rotation.x,
                                   glm::vec3( 1.0f, 0.0f, 0.0f ) );

    glm::quat roll = glm::rotate( glm::quat(), rotation.y,
                                  glm::vec3( 0.0f, 1.0f, 0.0f ) );

    _rotation = yaw * pitch * roll;
    recomputeMatrix();
}

// MEMBER FUNCTIONS
void Transform::rotateEuler( const glm::vec3& rotation )
{
    glm::quat rot = glm::rotate( _rotation, rotation.z,
                                 glm::vec3( 0.0f, 0.0f, 1.0f ) );

    rot = glm::rotate( rot, rotation.x, glm::vec3( 1.0f, 0.0f, 0.0f ) );
    rot = glm::rotate( rot, rotation.y, glm::vec3( 0.0f, 1.0f, 0.0f ) );

    _rotation = rot;
    recomputeMatrix();
}

void Transform::rotateAround( const glm::vec3& point,
                              const glm::quat& rotation )
{
    glm::vec4 pos = rotation * glm::vec4( _position - point, 1.0f );

    _position = glm::vec3( pos.x / pos.w, pos.y / pos.w, pos.z / pos.w ) +
        point;
    _rotation *= rotation;
    recomputeMatrix();
}

// HELPER FUNCTIONS
void Transform::recomputeMatrix()
{
    glm::mat4 trans;
    trans[3][0] = _position.x;
    trans[3][1] = _position.y;
    trans[3][2] = _position.z;

    glm::mat4 rot( glm::mat4_cast( _rotation ) );

    glm::mat4 scale( _scale );
    scale[3][3] = 1.0f;

    _matrix = trans * rot * scale;
    _hasChanged = true;
}

} // End nspc obj

} // End nspc demo