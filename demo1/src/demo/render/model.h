// model.h
//
// Container class for a 3D model.
//
#ifndef DEMO_MODEL_H
#define DEMO_MODEL_H

#include <assimp/scene.h>

#include "demo/render/irenderable.h"
#include "demo/strdef.h"

namespace demo
{

namespace rndr
{

class Model : public IRenderable
{
  private:
    /**
     * The model data.
     */
    const aiScene* _data;

    /**
     * The file path.
     */
    String _path;

    /**
     * Is the model on the GPU.
     */
    bool _isOnGpu;

    // HIDDEN FUNCTIONS
    /**
     * Hidden constructor.
     */
    Model( const Model& other ) = delete;

    /**
     * Hidden operator.
     */
    Model& operator=( const Model& other ) = delete;

  public:
    // CONSTRUCTORS
    /**
     * Construct a blank model.
     */
    Model();

    /**
     * Construct a new model from the file at the specified path.
     * @param path The model file path.
     * @param autoLoad Should the model automatically load.
     */
    Model( const String& path, bool autoLoad = false );

    /**
     * Destruct the model.
     */
    ~Model();

    // MEMBER FUNCTIONS
    /**
     * Load the model at the path specified during construction.
     * This does nothing if already loaded.
     * @throw File failed to load.
     */
    void load();

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
     */
    void push();

    /**
     * Render the model.
     * This does nothing if not on the GPU.
     */
    virtual void render();

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
Model::Model() : _data( nullptr ), _path(), _isOnGpu( false )
{
}

inline
Model::Model( const String& path, bool autoLoad )
        : _data( nullptr ), _path( path ), _isOnGpu( false )
{
    if ( autoLoad )
    {
        load( path );
    }
}

inline
Model::~Model()
{
    if ( _data != nullptr )
    {
        delete _data;
    }
}

// MEMBER FUNCTIONS
inline
void Model::load()
{
    load( _path );
}

inline
bool Model::isLoaded() const
{
    return _data != nullptr;
}

inline
bool Model::isOnGpu() const
{
    return _isOnGpu;
}

} // End nspc rndr

} // End nspc demo

#endif // DEMO_MODEL_H













