// transform.cpp
#include "transform.h"

#include <glm/gtc/matrix_transform.hpp>

namespace demo
{

namespace obj
{

// CONSTANTS
const glm::vec3 Transform::FORWARD( glm::vec3( 0, 0, -1 ) );
const glm::vec3 Transform::UP( glm::vec3( 0, 1, 0 ) );
const glm::vec3 Transform::RIGHT( glm::vec3( -1, 0, 0 ) );
const glm::vec3 Transform::ZERO( glm::vec3( 0, 0, 0 ) );

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

void Transform::lookAt( const glm::vec3& eye, const glm::vec3& center,
                        const glm::vec3& up )
{
    assert( eye != center );

    glm::vec3 forwardDir = glm::normalize( center - eye );
    glm::vec3 upDir = glm::normalize( up );

    glm::vec3 lookAxis = glm::cross( FORWARD, forwardDir );
    glm::vec3 upAxis = glm::cross( UP, upDir );

    // prevent zero axis
    if ( lookAxis == ZERO )
    {
        lookAxis = glm::vec3( 0, 0, 1 );
    }

    if ( upAxis == ZERO )
    {
        upAxis = glm::vec3( 0, 0, 1 );
    }

    lookAxis = glm::normalize( lookAxis );
    upAxis = glm::normalize( upAxis );

    float lookDot = glm::dot( FORWARD, forwardDir );
    float lookAngle =  acosf( lookDot );

    float upDot = glm::dot( UP, upDir );
    float upAngle = acosf( upDot );

    glm::quat lookQuat = glm::angleAxis( lookAngle, lookAxis );
    glm::quat upQuat = glm::normalize( glm::quat( upAxis * upAngle ) );

    _rotation = glm::quat_cast( glm::mat4_cast( lookQuat ) *
                                glm::mat4_cast( upQuat ) );
    _position = eye;

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

    glm::mat4 scale( _scale.x, 0, 0, 0,
                     0, _scale.y, 0, 0,
                     0, 0, _scale.z, 0,
                     0, 0, 0, 1 );

    _matrix = trans * rot * scale;
    _hasChanged = true;
}

} // End nspc obj

} // End nspc demo