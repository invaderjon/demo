// mesh.h
#include "mesh.h"

namespace demo
{

namespace rndr
{

// OPERATORS
Mesh& Mesh::operator=( const Mesh& other )
{
    if ( isOnGpu() )
    {
        remove();
    }

    _vertices = other._vertices;
    _indices = other._indices;
    _gl = GlMesh();
    _isOnGpu = false;

    return *this;
}

Mesh& Mesh::operator=( Mesh&& other )
{
    if ( isOnGpu() )
    {
        remove();
    }

    _vertices = std::move( other._vertices );
    _indices = std::move( other._indices );
    _gl = std::move( other._gl );
    _isOnGpu = other._isOnGpu;

    other._gl = GlMesh();
    other._isOnGpu = false;

    return *this;
}

// MEMBER FUNCTIONS
void Mesh::load( const aiMesh& mesh )
{
    if ( isOnGpu() )
    {
        remove();
    }

    _vertices = cntr::FixedArray<Vertex>( mesh.mNumVertices );
    _indices = cntr::FixedArray<uint32>( mesh.mNumFaces * 3 );

    loadAssimpMesh( mesh );
}

void Mesh::load( const cntr::FixedArray<Vertex>& vertices,
                 const cntr::FixedArray<uint32>& indices )
{
    if ( isOnGpu() )
    {
        remove();
    }

    _vertices = vertices;
    _indices = indices;
}

void Mesh::push( const Shader& shader )
{
    if ( isOnGpu() )
    {
        return;
    }

    // generate and bind vertex array object
    glGenVertexArrays( 1, &_gl.vao );
    glBindVertexArray( _gl.vao );

    // create vertex buffer
    glGenBuffers( 1, &_gl.vbo );
    glBindBuffer( GL_ARRAY_BUFFER, _gl.vbo );
    glBufferData( GL_ARRAY_BUFFER, _vertices.size() * sizeof( Vertex ),
                  &_vertices[0], GL_STATIC_DRAW );

    // create element buffer
    glGenBuffers( 1, &_gl.ebo );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _gl.ebo );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof( uint32 ),
                  &_indices[0], GL_STATIC_DRAW );

    // set up attributes
    uint32 posAttrib = shader.vertPositionAttrib();
    uint32 normAttrib = shader.vertNormalAttrib();

    glEnableVertexAttribArray( posAttrib );
    glVertexAttribPointer( posAttrib, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex ),
                           ( GLvoid* )offsetof( Vertex, position ) );

    glEnableVertexAttribArray( normAttrib );
    glVertexAttribPointer( normAttrib, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex ),
                           ( GLvoid* )offsetof( Vertex, normal) );

    // unbind vertex array object
    glBindVertexArray( 0 );

    _isOnGpu = true;
}

void Mesh::render( const Shader& shader )
{
    if ( !isOnGpu() )
    {
        return;
    }

    glBindVertexArray( _gl.vao );
    glDrawElements( GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0 );
    glBindVertexArray( 0 );
}

void Mesh::remove()
{
    if ( !isOnGpu() )
    {
        return;
    }

    glDeleteBuffers( 1, &_gl.ebo );
    glDeleteBuffers( 1, &_gl.vbo );
    glDeleteVertexArrays( 1, &_gl.vao );
    _isOnGpu = false;
}

// HELPER FUNCTIONS
void Mesh::loadAssimpMesh( const aiMesh& mesh )
{
    // transfer vertices
    for ( uint32 i = 0; i < mesh.mNumVertices; ++i )
    {
        Vertex vert;
        aiVector3D* pos = &mesh.mVertices[i];
        aiVector3D* norm = &mesh.mNormals[i];

        vert.position = glm::vec3( pos->x, pos->y, pos->z );
        vert.normal = glm::vec3( norm->x, norm->y, norm->z );

        _vertices.push( vert );
    }

    // transfer faces
    for ( uint32 i = 0; i < mesh.mNumFaces; ++i )
    {
        aiFace* face = &mesh.mFaces[i];

        _indices.push( face->mIndices[0] );
        _indices.push( face->mIndices[1] );
        _indices.push( face->mIndices[2] );
    }
}


} // End nspc rndr

} // End nspc demo