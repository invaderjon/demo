// material_factory.h
//
// A factory class that processes Assmip materials and generates native
// materials.
//
// The following properties are supported:
// Diffuse Color
// Specular Color
// shininess
//
// The following texture types are supported:
// Diffuse Maps
// Specular Maps
// Normal Maps
//
#ifndef DEMO_MATERIAL_FACTORY_H
#define DEMO_MATERIAL_FACTORY_H

#include <assimp/material.h>

#include "demo/render/material.h"

namespace demo
{

namespace res
{

class MaterialFactory
{
  private:
    // CONSTANTS
    /**
     * The number of supported texture types.
     */
    static constexpr uint32 TEXTURE_TYPE_COUNT = 3;

    /**
     * The array of supported texture types.
     */
    static constexpr aiTextureType TEXTURE_TYPES[TEXTURE_TYPE_COUNT] = {
            aiTextureType_DIFFUSE,
            aiTextureType_SPECULAR,
            aiTextureType_NORMALS
    };

    // HELPER FUNCTIONS
    /**
     * Get a texture from an Assimp material.
     * @param material The material.
     * @param type The texture type.
     * @return The material texture.
     */
    rndr::TexturePtr getTexture( const aiMaterial& material,
                                 aiTextureType type ) const;

    /**
     * Get a color from an Assimp material.
     * @param material The Assimp material.
     * @param name Assimp value: The name of the property.
     * @param type Assimp value: The property type.
     * @param idx Assimp value: The property index.
     * @param defValue The default value if not found.
     * @return The value
     */
    glm::vec3 getColor( const aiMaterial& material, const String& name,
                        uint32 type, uint32 idx,
                        const glm::vec3& defValue ) const;

    /**
     * Get a float from an Assimp model.
     * @param material The Assimp material.
     * @param name Assimp value: The name of the property.
     * @param type Assimp value: The property type.
     * @param idx Assimp value: The property index.
     * @param defValue The default value if not found.
     * @return The value.
     */
    float getFloat( const aiMaterial& material, const String& name,
                    uint32 type, uint32 idx, float defValue ) const;

  public:
    // CONSTRUCTORS
    /**
     * Construct a new MaterialFactory.
     */
    MaterialFactory();

    /**
     * Construct a copy of a MaterialFactory.
     * @param other The other MaterialFactory.
     */
    MaterialFactory( const MaterialFactory& other );

    /**
     * Destruct a MaterialFactory.
     */
    ~MaterialFactory();

    // OPERATORS
    /**
     * Assign this as a copy of another MaterialFactory.
     * @param other The other MaterialFactory.
     * @return This.
     */
    MaterialFactory& operator=( const MaterialFactory& other );

    // MEMBER FUNCTIONS
    /**
     * Create a native material from an assimp material.
     * @param material The Assimp material.
     * @param out Where to output the resulting material.
     */
    void create( const aiMaterial& material, rndr::MaterialPtr out );
};

// CONSTRUCTORS
inline
MaterialFactory::MaterialFactory()
{
}

inline
MaterialFactory::MaterialFactory( const MaterialFactory& other )
{
}

inline
MaterialFactory::~MaterialFactory()
{
}

// OPERATORS
inline
MaterialFactory& MaterialFactory::operator=( const MaterialFactory& other )
{
    return *this;
}

} // End nspc res

} // End nspc demo

#endif // DEMO_MATERIAL_FACTORY_H
