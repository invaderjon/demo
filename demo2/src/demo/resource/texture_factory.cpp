// texture_factory.cpp
#include "texture_factory.h"

#include <assert.h>
#include <FreeImage.h>

namespace demo
{

namespace res
{

// MEMBER FUNCTIONS
void TextureFactory::create( const String& path, rndr::Texture::Type type,
                             rndr::TexturePtr out )
{
    assert( out != nullptr );

    const char* filePath = path.c_str();

    // load image using FreeImage library
    FREE_IMAGE_FORMAT format = FreeImage_GetFileType( filePath, 0 );

    // ensure the image was found
    assert( format != 1 );

    // use file name to determine type if no magic number found
    if ( format == FIF_UNKNOWN )
    {
        // get format from file type and ensure it is supported
        format = FreeImage_GetFIFFromFilename( filePath );
        assert( FreeImage_FIFSupportsReading( format ) );
    }

    // determine the desired bits-per-pixel for the texture type
    uint8 desiredBpp;
    switch ( type )
    {
        case rndr::Texture::Type::BUMP:
        case rndr::Texture::Type::DIFFUSE:
        case rndr::Texture::Type::SPECULAR:
            desiredBpp = 24;
            break;

        default:
            desiredBpp = 32;
            break;
    }

    // read image
    FIBITMAP* bitmap = FreeImage_Load( format, filePath );
    FIBITMAP* formattedBitmap;

    bool isDesiredBpp = FreeImage_GetBPP( bitmap ) == desiredBpp;
    if ( isDesiredBpp )
    {
        formattedBitmap = bitmap;
    }
    else
    {
        switch (desiredBpp)
        {
            // 8-bit images (height maps, masks, transparency maps, etc.)
            case 8:
                formattedBitmap = FreeImage_ConvertTo8Bits( bitmap );
                break;

            // 24-bit images (most common alpha-less images)
            case 24:
                formattedBitmap = FreeImage_ConvertTo24Bits( bitmap );
                break;

            // 32-bit images (images with alpha [unnecessary in most cases])
            case 32:
            default:
                formattedBitmap = FreeImage_ConvertTo32Bits( bitmap );
                break;
        }
    }

    uint32 imageWidth = FreeImage_GetWidth( formattedBitmap );
    uint32 imageHeight = FreeImage_GetHeight( formattedBitmap );
    uint8* imageData = FreeImage_GetBits( formattedBitmap );
    uint32 size = imageWidth * imageHeight * ( desiredBpp / 8 );

    // load texture with data
    out->load( type, cntr::FixedArray<uint8>::copy( imageData, size, size ),
               imageWidth, imageHeight, desiredBpp );

    // release FreeImage resources
    FreeImage_Unload( formattedBitmap );
    if ( !isDesiredBpp )
    {
        FreeImage_Unload( bitmap );
    }
}

} // End nspc res

} // End nspc demo