// model_factory.cpp
#include "model_factory.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include "demo/resource/mesh_factory.h"
#include "material_factory.h"

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
    const aiScene* scene = importer.ReadFile( path,
                                              aiProcess_Triangulate |
                                              aiProcess_FixInfacingNormals |
                                              aiProcess_CalcTangentSpace );

    if ( scene == nullptr || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE ||
         !scene->mRootNode )
    {
        throw std::runtime_error( importer.GetErrorString() );
    }

    // process meshes
    cntr::FixedArray<rndr::Mesh> meshes( scene->mNumMeshes );
    processNode( &meshes, scene->mRootNode, scene );

    // process materials
    MaterialFactory materialFactory;
    cntr::FixedArray<rndr::Material> materials( scene->mNumMaterials );
    for ( uint32 i = 0; i < scene->mNumMaterials; ++i )
    {
        rndr::Material nativeMaterial;
        aiMaterial* material = scene->mMaterials[i];
        materialFactory.create( *material, &nativeMaterial );

        materials.push( std::move( nativeMaterial ) );
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