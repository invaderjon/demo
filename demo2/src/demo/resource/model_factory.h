// model_factory.h
//
// A factory class that processes Assimp models and generates native models.
//
#ifndef DEMO_MODEL_FACTORY_H
#define DEMO_MODEL_FACTORY_H

#include <assimp/scene.h>

#include "demo/render/model.h"

namespace demo
{

namespace res
{

class ModelFactory
{
  private:
    // HELPER FUNCTIONS
    /**
     * Process a node in the scene.
     * @param out The output array to store the meshes.
     * @param node The node.
     * @param scene The scene.
     */
    void processNode( cntr::FixedArray<rndr::Mesh>* out, aiNode* node,
                      const aiScene* scene );

  public:
    // CONSTRUCTORS
    /**
     * Construct a new ModelFactory.
     */
    ModelFactory();

    /**
     * Construct a copy of another ModelFactory.
     * @param other The other ModelFactory.
     */
    ModelFactory( const ModelFactory& other );

    /**
     * Destruct the ModelFactory.
     */
    ~ModelFactory();

    // OPERATORS
    /**
     * Assign this as a copy of another ModelFactory.
     * @param other The other ModelFactory.
     * @return This.
     */
    ModelFactory& operator=( const ModelFactory& other );

    // MEMBER FUNCTIONS
    /**
     * Create a model from an Assimp scene.
     * @param path The file path.
     * @param out The output model.
     */
    void create( const String& path, rndr::ModelPtr out );
};

// CONSTRUCTORS
inline
ModelFactory::ModelFactory()
{
}

inline
ModelFactory::ModelFactory( const ModelFactory& other )
{
}

inline
ModelFactory::~ModelFactory()
{
}

// OPERATORS
inline
ModelFactory& ModelFactory::operator=( const ModelFactory& other )
{
    return *this;
}

} // End nspc res

} // End nspc demo

#endif // DEMO_MODEL_FACTORY_H
