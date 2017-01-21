// texture.h
//
// An image that can be used during the rendering process.
//
#ifndef DEMO_TEXTURE_H
#define DEMO_TEXTURE_H

#include "demo/intdef.h"
#include "demo/container/fixed_array.h"
#include "demo/render/shader.h"

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
    // STRUCTURES
    struct GlTexture
    {
        /**
         * The OpenGL texture id.
         */
        uint32 id;

        /**
         * The OpenGL texture number.
         */
        uint32 textureInt;
    };

    // MEMBERS
    /**
     * The raw image data.
     */
    cntr::FixedArray<uint8> _data;

    /**
     * The OpenGL representation of a texture.
     */
    GlTexture _gl;

    /**
     * The texture type.
     */
    Type _type;

    /**
     * The texture width.
     */
    uint32 _width;

    /**
     * The texture height.
     */
    uint32 _height;

    /**
     * The number of bits per pixel.
     */
    uint8 _bpp;

    /**
     * Whether the texture is loaded.
     */
    bool _isLoaded;

    /**
     * Whether the texture is on the GPU.
     */
    bool _isOnGpu;

    /**
     * Whether the texture is bound.
     */
    bool _isBound;

    // HELPER FUNCTIONS
    /**
     * Get the type name for logging.
     * @return The type name.
     */
    String typeName() const;

    /**
     * Check if the tyep is UNKNOWN.
     * This is a convenience method.
     * @return Is unknown type?
     */
    bool isUnknownType() const;

  public:
    // ENUMERATIONS
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
        UNKNOWN = 0x80000000
    };

    // CONSTRUCTORS
    /**
     * Construct a blank texture.
     */
    Texture();

    /**
     * Construct a copy of another texture.
     * The copy will not be on the GPU and will not be bound.
     * @param other The other texture.
     */
    Texture( const Texture& other );

    /**
     * Move a texture to a new variable.
     * @param other The other texture.
     */
    Texture( Texture&& other );

    /**
     * Destruct the texture.
     */
    ~Texture();

    // OPERATORS
    /**
     * Assign this as a copy of another texture.
     * The copy will not be on the GPU and will not be bound.
     * @param other The other texture.
     * @return This.
     */
    Texture& operator=( const Texture& other );

    /**
     * Move a texture to this variable.
     * @param other The other texture.
     * @return This.
     */
    Texture& operator=( Texture&& other );

    // ACCESSOR FUNCTIONS
    /**
     * Get the texture type.
     * @return The type.
     */
    Type type() const;

    /**
     * Check if the texture is loaded.
     * @return Is it loaded?
     */
    bool isLoaded() const;

    /**
     * Check if the texture is on the GPU.
     * @return Is it on the GPU?
     */
    bool isOnGpu() const;

    /**
     * Check if the texture is bound.
     * @return Is it bound?
     */
    bool isBound() const;

    // MEMBER FUNCTIONS
     /**
      * Load the specified data.
      * @param data The image data.
      * @param width The width.
      * @param height The height.
      * @param bpp The bits per pixel.
      */
    void load( Type type, cntr::FixedArray<uint8>&& data, uint32 width,
               uint32 height, uint8 bpp );

    /**
     * Push the texture to the GPU.
     * This does nothing if not loaded.
     * This does nothing if already on the GPU.
     * This does nothing if the texture type is UNKNOWN.
     * @param shader The shader to bind to.
     */
    void push( const Shader& shader );

    /**
     * Bind the texture for rendering.
     * The texture must be unbound after being bound. Failure to do so is
     * considered an error.
     * This does nothing if not on the GPU.
     * This does nothing if the texture type is UNKNOWN.
     */
    void bind();

    /**
     * Unbind the texture for rendering.
     * This does nothing if not on the GPU.
     * This does nothing if the texture type is UNKNOWN.
     */
    void unbind();

    /**
     * Remove the texture from the GPU.
     * This does nothing if not on the GPU.
     * This does nothing if the texture type is UNKNOWN.
     */
    void remove();
};

// CONSTRUCTORS
inline
Texture::Texture() : _data( 1 ), _gl(), _type( Type::UNKNOWN ), _width( 0 ),
                     _height( 0 ), _bpp( 0 ), _isLoaded( false ),
                     _isOnGpu( false ), _isBound( false )
{
}

inline
Texture::Texture( const Texture& other )
        : _data( other._data ), _gl(), _type( other._type ),
          _width( other._width ), _height( other._height ), _bpp( other._bpp ),
          _isLoaded( other._isLoaded ), _isOnGpu( false ), _isBound( false )
{
}

inline
Texture::~Texture()
{
}

// ACCESSOR FUNCTIONS
inline
Texture::Type Texture::type() const
{
    return _type;
}

inline
bool Texture::isLoaded() const
{
    return _isLoaded;
}

inline
bool Texture::isOnGpu() const
{
    return _isOnGpu;
}

inline
bool Texture::isBound() const
{
    return _isBound;
}

// HELPER FUNCTIONS
inline
bool Texture::isUnknownType() const
{
    return _type == Type::UNKNOWN;
}

} // End nspc rndr

} // End nspc demo

#endif // DEMO_TEXTURE_H
