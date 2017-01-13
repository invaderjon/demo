// model.cpp
#include "model.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

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
void Model::load( const String& path )
{
    if ( isLoaded() )
    {
        return;
    }

    if ( path.empty() )
    {
        throw std::runtime_error( "File not specified!" );
    }

    // load file
    Assimp::Importer importer;
    const aiScene* data = importer.ReadFile( path, aiProcess_SortByPType );

    if ( !data )
    {
        throw std::runtime_error( importer.GetErrorString() );
    }

    // generate meshes
    for ( uint32 i = 0; i < data->mNumMeshes; ++i )
    {
        _meshes.push( std::move( Mesh( *( data->mMeshes[i] ) ) ) );
    }
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

    _isOnGpu = true;
}

void Model::render( const Shader& shader )
{
    if ( !isLoaded() || !isOnGpu() )
    {
        return;
    }

    for ( auto iter = _meshes.begin(); iter != _meshes.end(); ++iter )
    {
        iter->render( shader );
    }
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

    _isOnGpu = false;
}

} // End nspc rndr

} // End nspc demo