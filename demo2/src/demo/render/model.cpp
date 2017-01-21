// model.cpp
#include "model.h"

namespace demo
{

namespace rndr
{

// OPERATORS
Model& Model::operator=( Model&& other )
{
    if ( isOnGpu() )
    {
        remove();
    }

    _meshes = std::move( other._meshes );
    _isOnGpu = other._isOnGpu;

    other._isOnGpu = false;

    return *this;
}

// MEMBER FUNCTIONS
void Model::load( cntr::FixedArray<Mesh>&& meshes,
                  cntr::FixedArray<Material>&& materials )
{
    assert( !isOnGpu() );

    _meshes = std::move( meshes );
    _materials = std::move( materials );
    _isLoaded = true;
    _isOnGpu = false;
}

void Model::push( const Shader& shader )
{
    if ( isOnGpu() )
    {
        return;
    }

    for ( auto iter = _meshes.begin(); iter != _meshes.end(); ++iter )
    {
        iter->push( shader );
    }

    for ( auto iter = _materials.begin(); iter != _materials.end(); ++iter )
    {
        iter->push( shader );
    }

    GrApi::logError( "Model.push" );

    _isOnGpu = true;
}

void Model::render( const Shader& shader )
{
    if ( !isOnGpu() )
    {
        return;
    }

    for ( auto iter = _meshes.begin(); iter != _meshes.end(); ++iter )
    {
        if ( _materials.size() > 0 )
        {
            _materials[iter->materialIndex()].bind( shader );
        }

        iter->render( shader );

        if ( _materials.size() > 0 )
        {
            _materials[iter->materialIndex()].unbind();
        }
    }

    GrApi::logError( "Model.render" );
}

void Model::remove()
{
    if ( !isOnGpu() )
    {
        return;
    }

    for ( auto iter = _meshes.begin(); iter != _meshes.end(); ++iter )
    {
        iter->remove();
    }

    for ( auto iter = _materials.begin(); iter != _materials.end(); ++iter )
    {
        iter->remove();
    }

    GrApi::logError( "Model.remove" );

    _isOnGpu = false;
}

} // End nspc rndr

} // End nspc demo