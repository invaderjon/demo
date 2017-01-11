// model.cpp
#include "model.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <stdexcept>

namespace demo
{

namespace rndr
{

// MEMBER FUNCTIONS
void Model::load( const String& path )
{
    if ( isLoaded() )
    {
        return;
    }

    Assimp::Importer importer;

    _path = path;

    if ( _path.empty() )
    {
        throw std::runtime_error( "File not specified!" );
    }

    _data = importer.ReadFile( _path,
                               aiProcess_CalcTangentSpace |
                               aiProcess_Triangulate |
                               aiProcess_JoinIdenticalVertices |
                               aiProcess_SortByPType );

    if ( !_data )
    {
        throw std::runtime_error( importer.GetErrorString() );
    }
}

void Model::push()
{
    if ( isOnGpu() )
    {
        return;
    }
}

void Model::render()
{
}

} // End nspc rndr

} // End nspc demo