// mesh_factory.h
//
// A factory class that process Assimp meshes and generates native ones.
//
#ifndef DEMO_MESH_FACTORY_H
#define DEMO_MESH_FACTORY_H

#include <assimp/mesh.h>

#include "demo/render/mesh.h"

namespace demo
{

namespace res
{

class MeshFactory
{
  public:
    // CONSTRUCTORS
    /**
     * Construct a new MeshFactory.
     */
    MeshFactory();

    /**
     * Construct a copy of another MeshFactory.
     * @param other The other MeshFactory.
     */
    MeshFactory( const MeshFactory& other );

    /**
     * Destruct the MeshFactory.
     */
    ~MeshFactory();

    // OPERATORS
    /**
     * Assign this as a copy of another MeshFactory.
     * @param other The other MeshFactory.
     * @return This.
     */
    MeshFactory& operator=( const MeshFactory& other );

    // MEMBER FUNCTIONS
    /**
     * Create a native mesh from an Assimp mesh.
     * @param mesh The Assimp mesh.
     * @param out The output.
     */
    void create( const aiMesh& mesh, rndr::MeshPtr out );
};

// CONSTRUCTORS
inline
MeshFactory::MeshFactory()
{
}

inline
MeshFactory::MeshFactory( const MeshFactory& other )
{
}

inline
MeshFactory::~MeshFactory()
{
}

// OPERATORS
inline
MeshFactory& MeshFactory::operator=( const MeshFactory& other )
{
    return *this;
}

} // End nspc res

} // End nspc demo

#endif // DEMO_MESH_FACTORY_H
