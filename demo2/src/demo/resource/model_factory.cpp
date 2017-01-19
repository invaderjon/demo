// model_factory.cpp
#include "model_factory.h"

#include <assimp/Importer.hpp>

#include "demo/resource/mesh_factory.h"

namespace demo
{

namespace res
{

// MEMBER FUNCTIONS
void ModelFactory::create( const String& path, rndr::ModelPtr out )
{
    assert( out );
    assert( !path.empty() );

    // load file
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile( path, 0 );

    if ( scene == nullptr || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE ||
         !scene->mRootNode )
    {
        throw std::runtime_error( importer.GetErrorString() );
    }

    // process data
    cntr::FixedArray<rndr::Mesh> meshes( scene->mNumMeshes );
    processNode( &meshes, scene->mRootNode, scene );

    cntr::FixedArray<rndr::MaterialPtr> materials( scene->mNumMaterials );
    for ( uint32 i = 0; i < scene->mNumMaterials; ++i )
    {
        aiMaterial* material = scene->mMaterials[i];
        // todo: use resource manager to load each material
    }

    out->load( std::move( meshes ), std::move( materials ) );
}

// HELPER FUNCTIONS
void ModelFactory::processNode( cntr::FixedArray<rndr::Mesh>* out,
                                aiNode* node, const aiScene* scene )
{
    assert( node );
    assert( scene );

    // process the node's meshes (if any)
    MeshFactory meshFactory;
    for ( uint32 i = 0; i < node->mNumMeshes; ++i )
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

        rndr::Mesh nativeMesh;
        meshFactory.create( *mesh, &nativeMesh );
        out->push( std::move( nativeMesh ) );
    }

    for ( uint32 i = 0; i < node->mNumChildren; ++i )
    {
        processNode( out, node->mChildren[i], scene );
    }
}

} // End nspc res

} // End nspc demo