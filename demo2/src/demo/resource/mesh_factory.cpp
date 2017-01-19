// mesh_factory.cpp
#include "mesh_factory.h"

namespace demo
{

namespace res
{

// MEMBER FUNCTIONS
void MeshFactory::create( const aiMesh& mesh, rndr::MeshPtr out )
{
    // ensure that there is no more than one UV channel and if there is
    // a UV channel that it has exactly 2 components.
    assert( !mesh.HasTextureCoords( 1 ) );
    assert( !mesh.HasTextureCoords( 0 ) ||
            ( mesh.HasTextureCoords( 0 ) && mesh.mNumUVComponents[0] == 2 ) );

    cntr::FixedArray<rndr::Mesh::Vertex> vertices( mesh.mNumVertices );
    cntr::FixedArray<uint32> indices( mesh.mNumFaces * 3 );
    uint32 materialIndex( mesh.mMaterialIndex );

    bool hasUv = mesh.HasTextureCoords( 0 );

    // transfer vertices
    for ( uint32 i = 0; i < mesh.mNumVertices; ++i )
    {
        rndr::Mesh::Vertex vert;
        aiVector3D pos = mesh.mVertices[i];
        aiVector3D norm = mesh.mNormals[i];
        aiVector3D uv = hasUv ? mesh.mTextureCoords[i][0] : aiVector3D();

        vert.position = glm::vec3( pos.x, pos.y, pos.z );
        vert.normal = glm::vec3( norm.x, norm.y, norm.z );
        vert.texCoord = glm::vec2( uv.x, uv.y );

        vertices.push( vert );
    }

    // transfer faces
    for ( uint32 i = 0; i < mesh.mNumFaces; ++i )
    {
        aiFace* face = &mesh.mFaces[i];

        indices.push( face->mIndices[0] );
        indices.push( face->mIndices[1] );
        indices.push( face->mIndices[2] );
    }

    out->load( std::move( vertices ), std::move( indices ), materialIndex );
}

} // End nspc res

} // End nspc demo