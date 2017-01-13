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

	assert( !path.empty() );

    // load file
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile( path, aiProcess_Triangulate );

    if ( scene == nullptr || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE ||
            !scene->mRootNode )
    {
        throw std::runtime_error( importer.GetErrorString() );
    }

    // generate meshes
    processNode( scene->mRootNode, scene );
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

// HELPER FUNCTIONS
void Model::processNode( aiNode* node, const aiScene* scene )
{
    assert( node );
    assert( scene );

    // process the node's meshes (if any)
    for ( uint32 i = 0; i < node->mNumMeshes; ++i )
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        _meshes.push( std::move( Mesh( *mesh ) ) );
    }

    // process children
    for ( uint32 i = 0; i < node->mNumChildren; ++i )
    {
        processNode( node->mChildren[i], scene );
    }
}

} // End nspc rndr

} // End nspc demo