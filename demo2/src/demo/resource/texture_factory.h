// texture_factory.h
//
// Created by jonathan on 1/18/17.
//
#ifndef DEMO_TEXTURE_FACTORY_H
#define DEMO_TEXTURE_FACTORY_H

#include "demo/render/texture.h"
#include "demo/strdef.h"

namespace demo
{

namespace res
{

class TextureFactory
{
  public:
    // CONSTRUCTORS
    /**
     * Construct a new TextureFactory.
     */
    TextureFactory();

    /**
     * Construct a copy of another TextureFactory.
     * @param other The other TextureFactory.
     */
    TextureFactory( const TextureFactory& other );

    /**
     * Destruct a TextureFactory.
     */
    ~TextureFactory();

    // OPERATORS
    /**
     * Assign this as a copy of another TextureFactory.
     * @param other The other TextureFactory.
     * @return This.
     */
    TextureFactory& operator=( const TextureFactory& other );

    // MEMBER FUNCTIONS
    /**
     * Create a texture from the file at the specified path.
     * @param path The file path.
     * @param type The type of texture.
     * @param out The output location.
     */
    void create( const String& path, rndr::Texture::Type type,
                 rndr::TexturePtr out );
};

// CONSTRUCTORS
inline
TextureFactory::TextureFactory()
{
}

inline
TextureFactory::TextureFactory( const TextureFactory& other )
{
}

inline
TextureFactory::~TextureFactory()
{
}

// OPERATORS
inline
TextureFactory& TextureFactory::operator=( const TextureFactory& other )
{
    return *this;
}

} // End nspc res

} // End nspc demo

#endif // DEMO_TEXTURE_FACTORY_H
