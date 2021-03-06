// model.h
//
// Container class for a 3D model.
//
#ifndef DEMO_MODEL_H
#define DEMO_MODEL_H

#include "demo/intdef.h"
#include "demo/container/fixed_array.h"
#include "demo/render/irenderable.h"
#include "demo/render/mesh.h"
#include "demo/strdef.h"

namespace demo
{

namespace rndr
{

/**
 * Defines a model.
 */
class Model;

/**
 * Defines a pointer to a model.
 * This should be used anywhere a pointer would be used as this will eventually
 * be replaced with a smart pointer for the resource manager.
 */
typedef Model* ModelPtr;

class Model : public IRenderable
{
  private:
    // MEMBERS
    /**
     * The meshes that make up the model.
     */
    cntr::FixedArray<Mesh> _meshes;

    /**
     * The materials that are used by the meshes.
     */
    cntr::FixedArray<Material> _materials;

    /**
     * Whether the model has been loaded.
     */
    bool _isLoaded;

    /**
     * Whether the model on the GPU.
     */
    bool _isOnGpu;

  public:
    // CONSTRUCTORS
    /**
     * Construct an empty model.
     */
    Model();

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

    // ACCESSOR FUNCTIONS
    /**
     * Check if the model file has been loaded.
     * @return Is it loaded?
     */
    bool isLoaded() const;

    /**
     * Check if the model is on the GPU.
     * @return Is on the GPU?
     */
    bool isOnGpu() const;

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
     * Load the specified data.
     * It is an error to call this while the model is on the GPU.
     * @param meshes The meshes.
     * @param materials The materials.
     */
    void load( cntr::FixedArray<Mesh>&& meshes,
               cntr::FixedArray<Material>&& materials );

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
};

// CONSTRUCTORS
inline
Model::Model() : _meshes( 1 ), _materials( 1 ), _isLoaded(), _isOnGpu()
{
}

inline
Model::Model( const Model& other )
        : _meshes( other._meshes ), _materials( other._materials ),
          _isLoaded( other._isLoaded ), _isOnGpu()
{
}

inline
Model::Model( Model&& other ) : _meshes( std::move( other._meshes ) ),
                                _materials( std::move( other._materials ) ),
                                _isLoaded( other._isLoaded ),
                                _isOnGpu( other._isOnGpu )
{
    other._isLoaded = false;
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
    _materials = other._materials;
    _isLoaded = other._isLoaded;

    return *this;
}

// ACCESSOR FUNCTIONS
inline
bool Model::isLoaded() const
{
    return _isLoaded;
}

inline
bool Model::isOnGpu() const
{
    return _isOnGpu;
}

} // End nspc rndr

} // End nspc demo

#endif // DEMO_MODEL_H













