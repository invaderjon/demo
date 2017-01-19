// resource_manager.h
//
// Loads, manages, and unloads resources.
//
// todo list:
//  * Add ability to release resource
//  * Use a custom allocator that optimizes resource allocation
//  * Add reference counting with auto-unload
//  * Load asynchronously
//
#ifndef DEMO_RESOURCE_MANAGER_H
#define DEMO_RESOURCE_MANAGER_H

#include "demo/build.g.h"
#include "demo/container/map.h"
#include "demo/render/model.h"
#include "demo/render/texture.h"

namespace demo
{

namespace res
{

class ResourceManager
{
  private:
    // GLOBALS
    /**
     * The singleton instance.
     */
    static ResourceManager* g_instance;

    // MEMBERS
    /**
     * The set of loaded models.
     */
    cntr::Map<String, rndr::ModelPtr> _models;

    /**
     * The set of loaded textures.
     */
    cntr::Map<String, rndr::TexturePtr> _textures;

    /**
     * The model allocator.
     */
    mem::AllocatorGuard<rndr::Model> _modelAlloc;

    /**
     * The texture allocator.
     */
    mem::AllocatorGuard<rndr::Texture> _textureAlloc;

    // HELPER FUNCTIONS
    /**
     * Obtain the file path for the resource with the specified id.
     * @param resId The resource id.
     * @return The file path.
     */
    String obtainPath( const String& resId ) const;

  public:
    // GLOBAL METHODS
    /**
     * Initialize the resource manager.
     * This msut only be called once.
     */
    static void startup();

    /**
     * Get the singleton instance of the resource manager.
     * The resource manager singleton must be initialized using startup before
     * calling this method. Failure to do so is considered an error.
     * @return The resource manager.
     */
    static ResourceManager* inst();

    /**
     * Release the resource manager and all allocated resources.
     * The resource manager singleton must be initialized using startup before
     * calling this method. Failure to do so is considered an error.
     */
    static void shutdown();

    // CONSTRUCTORS
    /**
     * Construct a new resource manager.
     */
    ResourceManager();

    /**
     * Construct a copy of another resource manager.
     * @param other The other resource manager.
     */
    ResourceManager( const ResourceManager& other );

    /**
     * Destruct the resource manager.
     */
    ~ResourceManager();

    // OPERATORS
    /**
     * Assign this as a copy of another resource manager.
     * @param other The other resource manager.
     * @return This.
     */
    ResourceManager& operator=( const ResourceManager& other );

    // MEMBER FUNCTIONS
    /**
     * Load a model.
     * @param resId The resource id.
     * @return The model.
     */
    rndr::ModelPtr loadModel( const String& resId );

    /**
     * Load a texture.
     * Each texture is only allowed one type. Behavior is undefined otherwise.
     * @param resId The resource id.
     * @param type The desired texture type.
     * @return The texture.
     */
    rndr::TexturePtr loadTexture( const String& resId,
                                  rndr::Texture::Type type );
};

// GLOBAL METHODS
inline
void ResourceManager::startup()
{
    assert( g_instance == nullptr );
    g_instance = new ResourceManager();
}

inline
ResourceManager* ResourceManager::inst()
{
    assert( g_instance != nullptr );
    return g_instance;
}

inline
void ResourceManager::shutdown()
{
    assert( g_instance != nullptr );
    delete g_instance;
}

// CONSTRUCTORS
inline
ResourceManager::ResourceManager()
        : _models(), _textures(), _modelAlloc(), _textureAlloc()
{
}

inline
ResourceManager::ResourceManager( const ResourceManager& other )
        : _models( other._models ), _textures( other._textures ),
          _modelAlloc( other._modelAlloc ), _textureAlloc( other._textureAlloc )
{
}

// HELPER FUNCTIONS
inline
String ResourceManager::obtainPath( const String& resId ) const
{
    return DEMO_RES_PATH + '/' + resId;
}

} // End nspc res

} // End nspc demo

#endif // DEMO_RESOURCE_MANAGER_H
