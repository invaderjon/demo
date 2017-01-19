// resource_manager.cpp
#include "resource_manager.h"

#include "demo/render/model.h"
#include "demo/render/texture.h"
#include "demo/resource/model_factory.h"
#include "demo/resource/texture_factory.h"

namespace demo
{

namespace res
{

// GLOBALS
ResourceManager* ResourceManager::g_instance = nullptr;

// CONSTRUCTORS
ResourceManager::~ResourceManager()
{
    for ( auto iter = _models.cbegin(); iter != _models.cend(); ++iter )
    {
        _modelAlloc.release( iter->value, 1 );
    }

    for ( auto iter = _textures.cbegin(); iter != _textures.cend(); ++iter )
    {
        _textureAlloc.release( iter->value, 1 );
    }
}

// OPERATORS
ResourceManager& ResourceManager::operator=( const ResourceManager& other )
{
    _models = other._models;
    _textures = other._textures;
    _modelAlloc = other._modelAlloc;
    _textureAlloc = other._textureAlloc;

    return *this;
}

// MEMBER FUNCTIONS
rndr::ModelPtr ResourceManager::loadModel( const String& resId )
{
    rndr::ModelPtr ptr;
    if ( _models.has( resId ) )
    {
        ptr = _models[resId];
    }
    else
    {
        String path = obtainPath( resId );

        rndr::ModelPtr model = _modelAlloc.get( 1 );
        ModelFactory().create( path, model );
        _models.put( resId, model );

        ptr = model;
    }

    return ptr;
}

rndr::TexturePtr  ResourceManager::loadTexture( const String& resId,
                                                rndr::Texture::Type type )
{
    rndr::TexturePtr ptr;
    if ( _textures.has( resId ) )
    {
        ptr = _textures[resId];
        assert( type == ptr->type() );
    }
    else
    {
        String path = obtainPath( resId );

        rndr::TexturePtr texture = _textureAlloc.get( 1 );
        TextureFactory().create( path, type, texture );
        _textures.put( resId, texture );

        ptr = texture;
    }

    return ptr;
}

} // End nspc res

} // End nspc demo