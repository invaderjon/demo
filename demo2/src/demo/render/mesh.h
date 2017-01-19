// mesh.h
//
// A 3D representation of a renderable object.
//
// Mesh data must be triangulated prior to use.
// Mesh vertices must have exactly one UV coordinate set to have more is
// considered an error and behavior is undefined in such scenarios.
//
#ifndef DEMO_MESH_H
#define DEMO_MESH_H

#include <assimp/mesh.h>
#include <glm/glm.hpp>

#include "demo/container/fixed_array.h"
#include "demo/render/irenderable.h"
#include "demo/render/material.h"

namespace demo
{

namespace rndr
{

/**
 * Defines a mesh.
 */
class Mesh;

/**
 * Defines a pointer to a mesh.
 * This should be used anywhere a pointer would be used as this may eventually
 * be replaced with a smart pointer for the resource manager.
 */
typedef Mesh* MeshPtr;

class Mesh : public IRenderable
{
  public:
    /**
     * A mesh vertex.
     */
    struct Vertex;

  private:
    // STRUCTURES
    /**
     * The OpenGL mesh representation.
     */
    struct GlMesh
    {
        /**
         * The vertex array object.
         * This is a single object that binds a model and its data.
         */
        uint32 vao;

        /**
         * The vertex buffer object.
         * This is the object that stores the vertices.
         */
        uint32 vbo;

        /**
         * The element buffer object.
         * This is the object that stores the mesh faces.
         */
        uint32 ebo;
    };

    // MEMBERS
    /**
     * The vertices.
     */
    cntr::FixedArray<Vertex> _vertices;

    /**
     * The mesh vertex indices.
     */
    cntr::FixedArray<uint32> _indices;

    /**
     * The OpenGL representation.
     */
    GlMesh _gl;

    /**
     * The index of the material to use from the model.
     */
    uint32 _materialIndex;

    /**
     * Whether the mesh has been loaded.
     */
    bool _isLoaded;

    /**
     * Whether the mesh is on the GPU.
     */
    bool _isOnGpu;

  public:
    // STRUCTURES
    /**
     * A mesh vertex.
     */
    struct Vertex
    {
        /**
         * The vertex position.
         */
        glm::vec3 position;

        /**
         * The vertex normal.
         */
        glm::vec3 normal;

        /**
         * The vertex texture mapping coordinates.
         */
        glm::vec2 texCoord;
    };

    // CONSTANTS
    /**
     * The material index that means no material.
     */
    static constexpr uint32 NO_MATERIAL = static_cast<uint32>( -1 );

    // CONSTRUCTORS
    /**
     * Constructs an empty mesh.
     */
    Mesh();

    /**
     * Constructs a copy of another mesh.
     * The copy will not be on the GPU.
     * @param mesh The other mesh.
     */
    Mesh( const Mesh& other );

    /**
     * Move mesh to new variable.
     * @param other The mesh to copy.
     */
    Mesh( Mesh&& other );

    /**
     * Destruct the mesh.
     */
    ~Mesh();

    // OPERATORS
    /**
     * Assign this as a copy of another mesh.
     * The copy will not be on the GPU.
     * @param other The other mesh.
     * @return This.
     */
    Mesh& operator=( const Mesh& other );

    /**
     * Move a mesh to this variable.
     * @param other The other mesh.
     * @return This.
     */
    Mesh& operator=( Mesh&& other );

    // ACCESSOR FUNCTIONS
    /**
     * Get the index of the material used by the mesh.
     * @return The material index.
     */
    uint32 materialIndex() const;

    /**
     * Check if the mesh has been loaded.
     * @return Is it loaded?
     */
    bool isLoaded() const;

    /**
     * Check if the mesh is on the GPU.
     * @return Is on the GPU?
     */
    bool isOnGpu() const;

    // MEMBER FUNCTIONS
    /**
     * Load the given data.
     * This assumes a triangulated mesh.
     * This will cause the current data to be removed from the GPU.
     * @param vertices The mesh vertices.
     * @param indices The mesh indices.
     * @param materialIndex The index of the material to use.
     */
    void load( cntr::FixedArray<Vertex>&& vertices,
               cntr::FixedArray<uint32>&& indices,
               uint32 materialIndex );

    /**
     * Push the mesh to the GPU.
     * This does nothing if already on the GPU.
     * @param shader The shader to bind to.
     */
    void push( const Shader& shader );

    /**
     * Draw the mesh.
     * This does nothing if not on the GPU.
     * This must be rendered with the the same shader it was pushed with.
     * @param shader The shader to render with.
     */
    virtual void render( const Shader& shader );

    /**
     * Remove the mesh from the GPU.
     * This does nothing if not on the GPU.
     */
    void remove();
};

// CONSTRUCTORS
inline
Mesh::Mesh() : _vertices(), _indices(), _gl(), _materialIndex( NO_MATERIAL ),
               _isLoaded(), _isOnGpu()
{
}

inline
Mesh::Mesh( const Mesh& other )
        : _vertices( other._vertices ), _indices( other._indices ),
          _materialIndex( other._materialIndex ), _gl(),
          _isLoaded( other._isLoaded ), _isOnGpu()
{
}

inline
Mesh::Mesh( Mesh&& other ) : _vertices( std::move( other._vertices ) ),
                             _indices( std::move( other._indices ) ),
                             _materialIndex( other._materialIndex ),
                             _gl( std::move( other._gl ) ),
                             _isLoaded( other._isLoaded ),
                             _isOnGpu( other._isOnGpu )
{
    other._gl = GlMesh();
    other._materialIndex = NO_MATERIAL;
    other._isLoaded = false;
    other._isOnGpu = false;
}

inline
Mesh::~Mesh()
{
    if ( isOnGpu() )
    {
        remove();
    }
}

// ACCESSOR FUNCTIONS
inline
uint32 Mesh::materialIndex() const
{
    return _materialIndex;
}

// MEMBER FUNCTIONS
inline
bool Mesh::isLoaded() const
{
    return _isLoaded;
}

inline
bool Mesh::isOnGpu() const
{
    return _isOnGpu;
}

} // End nspc rndr

} // End nspc demo

#endif // DEMO_MESH_H
