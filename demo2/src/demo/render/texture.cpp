// texture.cpp
#include "texture.h"

#include <FreeImage.h>

namespace demo
{

namespace rndr
{

// CONSTRUCTORS
Texture::Texture( Texture&& other )
        : _data( std::move( other._data ) ), _gl( std::move( other._gl ) ),
          _type( other._type ), _width( other._width ),
          _height( other._height ), _bpp( other._bpp ),
          _isLoaded( other._isLoaded ), _isOnGpu( other._isOnGpu ),
          _isBound( other._isBound )
{
    other._gl = GlTexture();
    other._type = Type::UNKNOWN;
    other._width = 0;
    other._height = 0;
    other._bpp = 0;
    other._isLoaded = false;
    other._isOnGpu = false;
    other._isBound = false;
}

// OPERATORS
Texture& Texture::operator=( const Texture& other )
{
    if ( isBound() )
    {
        unbind();
    }

    if ( isOnGpu() )
    {
        remove();
    }

    _data = other._data;
    _gl = GlTexture();
    _type = other._type;
    _width = other._width;
    _height = other._height;
    _bpp = other._bpp;
    _isLoaded = other._isLoaded;
    _isOnGpu = false;
    _isBound = false;

    return *this;
}

Texture& Texture::operator=( Texture&& other )
{
    _data = std::move( other._data );
    _gl = std::move( other._gl );
    _type = other._type;
    _width = other._width;
    _height = other._height;
    _bpp = other._bpp;
    _isLoaded = other._isLoaded;
    _isOnGpu = other._isOnGpu;
    _isBound = other._isBound;

    other._gl = GlTexture();
    other._type = Type::UNKNOWN;
    other._width = 0;
    other._height = 0;
    other._bpp = 0;
    other._isLoaded = false;
    other._isOnGpu = false;
    other._isBound = false;

    return *this;
}

// MEMBER FUNCTIONS
void Texture::load( cntr::FixedArray<uint8>&& data, uint32 width, uint32 height,
                    uint8 bpp )
{
    _data = std::move( data );
    _width = width;
    _height = height;
    _bpp = bpp;

    _isLoaded = true;
}

void Texture::push( const Shader& shader )
{
    if ( !isLoaded() || isOnGpu() || isUnknownType() )
    {
        return;
    }

    uint32 cpuFormat;
    uint32 gpuFormat;

    // 8-bit formats so I don't forget in later demos
//    cpuFormat = GL_LUMINANCE8;
//    gpuFormat = GL_LUMINANCE;

    // determine data formats
    switch ( _type )
    {
        case Type::DIFFUSE:
        case Type::SPECULAR:
        case Type::BUMP:
            #if FREEIMAGE_COLORORDER == FREEIMAGE_COLORORDER_BGR
            cpuFormat = GL_BGR;
            #else
            cpuFormat = GL_RGB;
            #endif

            gpuFormat = GL_RGB;
            break;

        default:
            #if FREEIMAGE_COLORORDER == FREEIMAGE_COLORORDER_BGR
            cpuFormat = GL_BGRA;
            #else
            cpuFormat = GL_RGBA;
            #endif

            gpuFormat = GL_RGBA;
            break;
    }

    // push data to GPU
    glGenTextures( 1, &_gl.id );
    glBindTexture( GL_TEXTURE_2D, _gl.id );
    glTexImage2D( GL_TEXTURE_2D,
                  0,
                  gpuFormat,
                  _width,
                  _height,
                  0,
                  cpuFormat,
                  GL_UNSIGNED_BYTE,
                  _data.data() );

    // generate mip maps (requires OpenGL 3.0)
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                     GL_LINEAR_MIPMAP_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                     GL_LINEAR_MIPMAP_LINEAR );
    glGenerateMipmap( GL_TEXTURE_2D );

    glBindTexture( GL_TEXTURE_2D, 0 );

    // store which GL texture it should bind to for later
    switch ( _type )
    {
        case Type::DIFFUSE:
            _gl.textureInt = GL_TEXTURE0;
            break;

        case Type::SPECULAR:
            _gl.textureInt  = GL_TEXTURE1;
            break;

        case Type::BUMP:
            _gl.textureInt  = GL_TEXTURE2;
            break;

        default:
            // only the above texture types are supported
            // anything else is a failure
            assert( false );
            break;
    }

    _isOnGpu = true;
}

void Texture::bind()
{
    if ( !isOnGpu() || isUnknownType() )
    {
        return;
    }

    // bind the texture
    glActiveTexture( _gl.textureInt );
    glBindTexture( GL_TEXTURE_2D, _gl.id );

    _isBound = true;
}

void Texture::unbind()
{
    if ( !isOnGpu() || isUnknownType() )
    {
        return;
    }

    glActiveTexture( _gl.textureInt );
    glBindTexture( GL_TEXTURE_2D, 0 );

    _isBound = false;
}

void Texture::remove()
{
    if ( !isOnGpu() || isUnknownType() )
    {
        return;
    }

    glDeleteTextures( 1, &_gl.id );

    _isOnGpu = false;
}

} // End nspc rndr

} // End nspc demo