// mesh.h
//
// A 3D representation of a renderable object.
//
// Mesh data must be triangulated prior to use.
//
#ifndef DEMO_MESH_H
#define DEMO_MESH_H

#include <assimp/mesh.h>
#include <glm/glm.hpp>

#include "demo/container/fixed_array.h"
#include "demo/render/irenderable.h"

namespace demo
{

namespace rndr
{

class Mesh : public IRenderable
{
  private:
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
    };

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
     * Whether the mesh is on the GPU.
     */
    bool _isOnGpu;

    // HELPER FUNCTIONS
    /**
     * Load an Assimp mesh.
     */
    void loadAssimpMesh( const aiMesh& mesh );

  public:
    // CONSTRUCTORS
    /**
     * Constructs an empty mesh.
     */
    Mesh();

    /**
     * Construct a mesh from an Assimp mesh.
     * This assumes a triangulated mesh.
     * @param mesh The Assimp mesh.
     */
    Mesh( const aiMesh& mesh );

    /**
     * Construct a mesh with the given data.
     * This assumes a triangulated mesh.
     * @param vertices The mesh vertices.
     * @param indices The mesh indices.
     */
    Mesh( const cntr::FixedArray<Vertex>& vertices,
          const cntr::FixedArray<uint32>& indices );

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

    // MEMBER FUNCTIONS
    /**
     * Load the Assimp mesh.
     * This assumes a triangulated mesh.
     * This will cause the current data to be removed from the GPU.
     * @param mesh The Assimp mesh.
     */
    void load( const aiMesh& mesh );

    /**
     * Load the given data.
     * This assumes a triangulated mesh.
     * This will cause the current data to be removed from the GPU.
     * @param vertices The mesh vertices.
     * @param indices The mesh indices.
     */
    void load( const cntr::FixedArray<Vertex>& vertices,
               const cntr::FixedArray<uint32>& indices );

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

    /**
     * Check if the mesh is on the GPU.
     * @return Is on the GPU?
     */
    bool isOnGpu() const;
};

// CONSTRUCTORS
inline
Mesh::Mesh() : _vertices(), _indices(), _gl(), _isOnGpu()
{
}

inline
Mesh::Mesh( const aiMesh& mesh ): _vertices( mesh.mNumVertices ),
                                  _indices( mesh.mNumFaces * 3 ),
                                  _gl(), _isOnGpu()
{
    loadAssimpMesh( mesh );
}

inline
Mesh::Mesh( const cntr::FixedArray<Vertex>& vertices,
            const cntr::FixedArray<uint32>& indices )
        : _vertices( vertices ), _indices( indices ), _gl(), _isOnGpu()
{
}

inline
Mesh::Mesh( const Mesh& other )
        : _vertices( other._vertices ), _indices( other._indices ),
          _gl(), _isOnGpu()
{
}

inline
Mesh::Mesh( Mesh&& other ) : _vertices( std::move( other._vertices ) ),
                             _indices( std::move( other._indices ) ),
                             _gl( std::move( other._gl ) ),
                             _isOnGpu( other._isOnGpu )
{
    other._gl = GlMesh();
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

// MEMBER FUNCTIONS
inline
bool Mesh::isOnGpu() const
{
    return _isOnGpu;
}

} // End nspc rndr

} // End nspc demo

#endif // DEMO_MESH_H
