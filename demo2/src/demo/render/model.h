// model.h
//
// Container class for a 3D model.
//
#ifndef DEMO_MODEL_H
#define DEMO_MODEL_H

#include <assimp/scene.h>

#include "demo/intdef.h"
#include "demo/container/dynamic_array.h"
#include "demo/render/irenderable.h"
#include "demo/render/mesh.h"
#include "demo/strdef.h"

namespace demo
{

namespace rndr
{

class Model : public IRenderable
{
  private:
    // MEMBERS
    /**
     * The meshes that make up the model.
     */
    cntr::DynamicArray<Mesh> _meshes;

    /**
     * Is the model on the GPU.
     */
    bool _isOnGpu;

    // HELPER FUNCTIONS
    /**
     * Process the specified node.
     * @param node The node to process.
     * @param scene The scene that the node is in.
     */
    void processNode( aiNode* node, const aiScene* scene );

  public:
    // CONSTRUCTORS
    /**
     * Construct an empty model.
     */
    Model();

    /**
     * Construct a new model from the file at the specified path.
     * This will immediately load the file.
     * @param path The model file path.
     */
    Model( const String& path );

    /**
     * Construct a copy of another model.
     * The copy will not be on the GPU.
     * @param other The other model.
     */
    Model( const Model& other );

    /**
     * Move model to new variable.
     * @param other The model to copy.
     */
    Model( Model&& other );

    /**
     * Destruct the model.
     */
    ~Model();

    // OPERATORS
    /**
     * Assign as a copy of another model.
     * The copy will not be on the GPU.
     * @param other The other model.
     * @return This.
     */
    Model& operator=( const Model& other );

    /**
     * Move a model to this variable.
     * @param other The other model.
     * @return This.
     */
    Model& operator=( Model&& other );

    // MEMBER FUNCTIONS
    /**
     * Load the model at the specified path.
     * If a file was specified during construction this will override it.
     * This does nothing if already loaded.
     * @param path The file path.
     * @throw File failed to load.
     */
    void load( const String& path );

    /**
     * Push the model's data to the GPU.
     * This does nothing if already on the GPU.
     * @param shader The shader to bind to.
     */
    void push( const Shader& shader );

    /**
     * Render the model.
     * This does nothing if not on the GPU.
     * This must be rendered with the the same shader it was pushed with.
     * @param shader The shader to render with.
     */
    virtual void render( const Shader& shader );

    /**
     * Remove from the GPU.
     * This does nothing if not on the GPU.
     */
    void remove();

    /**
     * Check if the model is on the GPU.
     * @return Is on the GPU?
     */
    bool isOnGpu() const;

    /**
     * Check if the model file has been loaded.
     * @return Is it loaded?
     */
    bool isLoaded() const;
};

// CONSTRUCTORS
inline
Model::Model() : _meshes(), _isOnGpu( false )
{
}

inline
Model::Model( const String& path ) : _meshes(), _isOnGpu( false )
{
    load( path );
}

inline
Model::Model( const Model& other ) : _meshes( other._meshes ), _isOnGpu()
{
}

inline
Model::Model( Model&& other ) : _meshes( std::move( other._meshes ) ),
                                _isOnGpu( other._isOnGpu )
{
    other._isOnGpu = false;
}

inline
Model::~Model()
{
}

// OPERATORS
inline
Model& Model::operator=( const Model& other )
{
    if ( isOnGpu() )
    {
        remove();
    }

    _meshes = other._meshes;

    return *this;
}

// MEMBER FUNCTIONS
inline
bool Model::isLoaded() const
{
    return _meshes.size() > 0;
}

inline
bool Model::isOnGpu() const
{
    return _isOnGpu;
}

} // End nspc rndr

} // End nspc demo

#endif // DEMO_MODEL_H













