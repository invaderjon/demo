// material.cpp
#include "material.h"

#include <glm/gtc/type_ptr.hpp>

namespace demo
{

namespace rndr
{

// CONSTRUCTORS
Material::Material( Material&& other )
        : _textures( std::move( other._textures ) ),
          _diffColor( std::move( other._diffColor ) ),
          _specColor( std::move( other._specColor ) ),
          _shininess( other._shininess ),
          _texFlags( other._texFlags ),
          _isLoaded( other._isLoaded ),
          _isBound( other._isBound )
{
    other._diffColor = glm::vec3();
    other._specColor = glm::vec3();
    other._shininess = 0.0f;
    other._texFlags = 0;
    other._isLoaded = false;
    other._isBound = false;
}

// OPERATORS
Material& Material::operator=( const Material& other )
{
    if ( isBound() )
    {
        unbind();
    }

    _textures = other._textures;
    _diffColor = other._diffColor;
    _specColor = other._specColor;
    _shininess = other._shininess;
    _texFlags = other._texFlags;
    _isLoaded = other._isLoaded;
    _isBound = false;

    return *this;
}

Material& Material::operator=( Material&& other )
{
    if ( isBound() )
    {
        unbind();
    }

    _textures = std::move( other._textures );
    _diffColor = std::move( other._diffColor );
    _specColor = std::move( other._specColor );
    _shininess = other._shininess;
    _texFlags = other._texFlags;
    _isLoaded = other._isLoaded;
    _isBound = other._isBound;

    other._diffColor = glm::vec3();
    other._specColor = glm::vec3();
    other._shininess = 0.0f;
    other._texFlags = 0;
    other._isLoaded = false;
    other._isBound = false;

    return *this;
}

// MEMBER FUNCTIONS
void Material::load( cntr::DynamicArray<TexturePtr>&& textures,
                     glm::vec3&& diffColor, glm::vec3&& specColor,
                     float shininess )
{
    assert( !isLoaded() );

    _textures = std::move( textures );
    _diffColor = std::move( diffColor );
    _specColor = std::move( specColor );
    _shininess = shininess;

    _texFlags = 0;
    for ( auto iter = _textures.cbegin(); iter != _textures.cend(); ++iter )
    {
        assert( ( _texFlags & ( *iter )->type() ) == 0 );
        _texFlags |= ( *iter )->type();
    }

    _isBound = false;
    _isLoaded = true;
}

void Material::bind( const Shader& shader )
{
    if ( !isLoaded() )
    {
        return;
    }

    // bind textures
    for ( auto iter = _textures.begin(); iter != _textures.end(); ++iter )
    {
        ( *iter )->bind();
    }

    glUniform3fv( shader.colorDiffuse(), 1, glm::value_ptr( _diffColor ) );
    glUniform3fv( shader.colorSpecular(), 1, glm::value_ptr( _specColor ) );
    glUniform1f( shader.valShininess(), _shininess );
    glUniform1ui( shader.valMatFlags(), _texFlags );

    GrApi::logError( "Material.bind" );
}

void Material::unbind()
{
    if ( !isLoaded() )
    {
        return;
    }

    // unbind textures
    for ( auto iter = _textures.begin(); iter != _textures.end(); ++iter )
    {
        ( *iter )->unbind();
    }

    GrApi::logError( "Material.unbind" );
}

} // End nspc rndr

} // End nspc demo