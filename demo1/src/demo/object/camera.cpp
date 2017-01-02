// camera.cpp
#include "camera.h"

namespace demo
{

namespace obj
{

// OPERATORS
Camera& Camera::operator=( const Camera& other )
{
    _fieldOfView = other._fieldOfView;
    _nearPlane = other._nearPlane;
    _farPlane = other._farPlane;
    return *this;
}

} // End nspc obj

} // End nspc demo