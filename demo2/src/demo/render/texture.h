// texture.h
//
// An image that can be used during the rendering process.
//
#ifndef DEMO_TEXTURE_H
#define DEMO_TEXTURE_H

#include "demo/intdef.h"

namespace demo
{

namespace rndr
{

/**
 * Defines a texture.
 */
class Texture;

/**
 * Defines a pointer to a texture.
 * This should be used anywhere a pointer would be used as this will eventually
 * be replaced with a smart pointer for the resource manager.
 */
typedef Texture* TexturePtr;

class Texture
{
  public:
    // ENUMERATIONS
    /**
     * Defines the type of texture.
     */
    enum Type : uint32;

  private:
    // MEMBERS
    /**
     * The texture type.
     */
    Type _type;

  public:
    /**
     * Defines the type of texture.
     */
    enum Type : uint32
    {
        /**
         * A diffuse map.
         */
        DIFFUSE = 0x1,

        /**
         * A specularity map.
         */
        SPECULAR = 0x2,

        /**
         * A bump/normal map.
         */
        BUMP = 0x4,

        /**
         * An unknown texture type.
         */
        UNKNOWN
    };

    // ACCESSOR FUNCTIONS
    /**
     * Get the texture type.
     * @return The type.
     */
    Type type() const;
};

// ACCESSOR FUNCTIONS
inline
Texture::Type Texture::type() const
{
    return _type;
}

} // End nspc rndr

} // End nspc demo

#endif // DEMO_TEXTURE_H
