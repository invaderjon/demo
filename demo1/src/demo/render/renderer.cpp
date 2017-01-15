// renderer.cpp
#include "renderer.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

namespace demo
{

namespace rndr
{

void Renderer::render( const obj::Camera& camera, const obj::Scene& scene )
{
    if ( !_shader->isActive() )
    {
        _shader->activate();
    }

    if ( !_target->isActive() )
    {
        _target->activate();
    }

    // compute projection matrix
    glm::mat4 project = glm::perspective( glm::radians( camera.fieldOfView() ),
                                          _target->aspectRatio(),
                                          camera.nearPlane(),
                                          camera.farPlane() );

    glm::mat4 view = glm::inverse( camera.transform().matrix() );

    // push frame-constant matrices to GPU
    glUniformMatrix4fv( _shader->matProjectionAttr(), 1, GL_FALSE,
                        glm::value_ptr( project ) );

    glUniformMatrix4fv( _shader->matViewAttrib(), 1, GL_FALSE,
                        glm::value_ptr( view ) );

    // render objects
    cntr::DynamicArray<obj::Object*> objects = scene.getObjects();
    for ( auto iter = objects.begin();
          iter != objects.end();
          ++iter )
    {
        if ( ( *iter )->isRenderable() && ( *iter )->isEnabled() )
        {
            // get matrices
            glm::mat4 model = ( *iter )->transform().matrix();
            glm::mat3 normal = glm::mat3( glm::transpose( glm::inverse(
                    view * model ) ) );

            // push matrices
            glUniformMatrix4fv( _shader->matModelAttrib(), 1, GL_FALSE,
                                glm::value_ptr( model ) );

            glUniformMatrix3fv( _shader->matNormalAttrib(), 1, GL_FALSE,
                                glm::value_ptr( normal ) );

            // render object
            ( *iter )->render( *_shader );
        }
    }
}

} // End nspc rndr

} // End nspc demo