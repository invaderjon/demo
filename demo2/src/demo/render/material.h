// material.h
//
// Container class for a mesh's textures and lighting settings.
//
// Materials may have at most one instance of each type of texture. To have
// more than one texture for a singular type is considered an error and as such
// behavior is undefined.
//
// When a material has both a diffuse color and a diffuse map the diffuse color
// is multiplied by the diffuse texture sample. This allows for tinting. To
// avoid this the diffuse color must be white (1.0f, 1.0f, 1.0f).
//
// When a material has a specularity map the shininess value is ignored.
//
// An alpha channel is prohibited in textures, instead an alpha mask should be
// used. See the Texture class for more details.
//
#ifndef DEMO_MATERIAL_H
#define DEMO_MATERIAL_H

#include <glm/glm.hpp>

#include "demo/container/dynamic_array.h"
#include "demo/render/shader.h"
#include "demo/render/texture.h"
#include "demo/strdef.h"

namespace demo
{

namespace rndr
{

/**
 * Defines a material.
 */
class Material;

/**
 * Defines a pointer to a material.
 * This should be used anywhere a pointer would be used as this may eventually
 * be replaced with a smart pointer for the resource manager.
 */
typedef Material* MaterialPtr;

class Material
{
  private:
    // MEMBERS
    /**
     * The textures used by the material.
     */
    cntr::DynamicArray<TexturePtr> _textures;

    /**
     * The diffuse shading color.
     */
    glm::vec3 _diffColor;

    /**
     * The specular reflection color.
     */
    glm::vec3 _specColor;

    /**
     * The object's shininess.
     */
    float _shininess;

    /**
     * The generated texture flags used by the shader.
     */
    uint32 _texFlags;

    /**
     * Is the material loaded?
     */
    bool _isLoaded;

    /**
     * Whether or not the material is bound.
     */
    bool _isBound;

  public:
    // CONSTRUCTORS
    /**
     * Construct a blank material.
     */
    Material();

    /**
     * Constructs a copy of another material.
     * The copy will not be bound.
     * @param other The other material.
     */
    Material( const Material& other );

    /**
     * Move material to new variable.
     * @param other The material to copy.
     */
    Material( Material&& other );

    /**
     * Destruct the material.
     */
    ~Material();

    // OPERATORS
    /**
     * Assign this as a copy of another material.
     * The copy will not be bound.
     * @param other The other material.
     * @return This.
     */
    Material& operator=( const Material& other );

    /**
     * Move a material to this variable.
     * @param other The other material.
     * @return This.
     */
    Material& operator=( Material&& other );

    // ACCESSOR FUNCTIONS
    /**
     * Has the material finished loading?
     * @return Is it loaded?
     */
    bool isLoaded() const;

    /**
     * Check if the material is bound.
     * @return Is it bound?
     */
    bool isBound() const;

    // MEMBER FUNCTIONS
    /**
     * Load the specified data.
     * @param textures The textures.
     * @param diffColor The diffuse color.
     * @param specColor The specular color.
     * @param shininess The shininess.
     */
    void load( cntr::DynamicArray<TexturePtr>&& textures,
               glm::vec3&& diffColor,
               glm::vec3&& specColor,
               float shininess );

    /**
     * Bind the texture for rendering.
     * @param shader The shader to bind to.
     */
    void bind( const Shader& shader );

    /**
     * Unbind the texture after rendering.
     * This must be called after bind. Failure to do so is considered
     * an error.
     */
    void unbind();
};

// CONSTRUCTORS
inline
Material::Material() : _textures( 1 ), _diffColor( 1.0f ), _specColor( 1.0f ),
                       _shininess( 0.0f ), _texFlags(), _isLoaded(),
                       _isBound()
{
}

inline
Material::Material( const Material& other )
        : _textures( other._textures ), _diffColor( other._diffColor ),
          _specColor( other._specColor ), _shininess( other._shininess ),
          _texFlags( other._texFlags ), _isLoaded( other._isLoaded ),
          _isBound()
{
}

inline
Material::~Material()
{
}

// ACCESSOR FUNCTIONS
inline
bool Material::isLoaded() const
{
    return _isLoaded;
}

inline
bool Material::isBound() const
{
    return _isBound;
}

} // End npsc rndr

} // End nspc demo

#endif // DEMO_MATERIAL_H
