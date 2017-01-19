// texture_factory.cpp
#include "texture_factory.h"

#include <assert.h>

namespace demo
{

namespace res
{

// MEMBER FUNCTIONS
void TextureFactory::create( const String& path, rndr::Texture::Type type,
                             rndr::TexturePtr out )
{
    assert( out != nullptr );

    // todo: load image
}

} // End nspc res

} // End nspc demo