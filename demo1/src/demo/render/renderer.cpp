// renderer.cpp
#include "renderer.h"

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

    cntr::DynamicArray<obj::Object*> objects = scene.getObjects();
    for ( auto iter = objects.begin();
          iter != objects.end();
          iter )
    {
        if ( ( *iter )->isRenderable() && ( *iter )->isEnabled() )
        {
            ( *iter )->render();
        }
    }
}

} // End nspc rndr

} // End nspc demo