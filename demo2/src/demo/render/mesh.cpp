// mesh.h
#include "mesh.h"

#include <iostream>

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
    _materialIndex = other._materialIndex;
    _isLoaded = other._isLoaded;
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
    _materialIndex = other._materialIndex;
    _isLoaded = other._isLoaded;
    _isOnGpu = other._isOnGpu;

    other._gl = GlMesh();
    other._materialIndex = NO_MATERIAL;
    other._isLoaded = false;
    other._isOnGpu = false;

    return *this;
}

// MEMBER FUNCTIONS
void Mesh::load( cntr::FixedArray<Vertex>&& vertices,
                 cntr::FixedArray<uint32>&& indices,
                 uint32 materialIndex )
{
    if ( isOnGpu() )
    {
        remove();
    }

    _vertices = std::move( vertices );
    _indices = std::move( indices );
    _materialIndex = materialIndex;

    _isLoaded = true;
}

void Mesh::push( const Shader& shader )
{
    if ( !isLoaded() || isOnGpu() )
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
    uint32 posAttr = shader.vertPositionAttr();
    uint32 normAttr = shader.vertNormalAttr();
    uint32 texCoordAttr = shader.vertTexCoordAttr();

    glEnableVertexAttribArray( posAttr );
    glVertexAttribPointer( posAttr, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex ),
                           ( GLvoid* )offsetof( Vertex, position ) );

    glEnableVertexAttribArray( normAttr );
    glVertexAttribPointer( normAttr, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex ),
                           ( GLvoid* )offsetof( Vertex, normal) );

    glEnableVertexAttribArray( texCoordAttr );
    glVertexAttribPointer( texCoordAttr, 2, GL_FLOAT, GL_FALSE,
                           sizeof( Vertex ),
                           ( GLvoid* )offsetof( Vertex, texCoord ) );

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

} // End nspc rndr

} // End nspc demo