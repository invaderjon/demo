// material_factory.h
#include "material_factory.h"

#include "demo/resource/resource_manager.h"

namespace demo
{

namespace res
{

// CONSTANTS
constexpr aiTextureType MaterialFactory::TEXTURE_TYPES[];

// MEMBER FUNCTIONS
void MaterialFactory::create( const aiMaterial& material,
                              rndr::MaterialPtr out )
{
    assert( out != nullptr );

    // get textures
    cntr::DynamicArray<rndr::TexturePtr> textures;
    rndr::TexturePtr texture;
    for ( uint32 i = 0; i < TEXTURE_TYPE_COUNT; ++i )
    {
        texture = getTexture( material, MaterialFactory::TEXTURE_TYPES[i] );
        if ( texture != nullptr )
        {
            textures.push( texture );
        }
    }

    // get properties
    glm::vec3 diffColor = getColor( material, AI_MATKEY_COLOR_DIFFUSE,
                                    glm::vec3( 1.0f ) );

    glm::vec3 specColor = getColor( material, AI_MATKEY_COLOR_SPECULAR,
                                    glm::vec3( 1.0f ) );

    float shininess = getFloat( material, AI_MATKEY_SHININESS, 0.0f );

    // apply to the object
    out->load( std::move( textures ), std::move( diffColor ),
               std::move( specColor ), shininess );
}

// HELPER FUNCTIONS
rndr::TexturePtr MaterialFactory::getTexture( const aiMaterial& material,
                                              aiTextureType type ) const
{
    if ( material.GetTextureCount( type ) <= 0 )
    {
        return nullptr;
    }

    aiString path;
    if ( material.GetTexture( type, 0, &path ) == AI_FAILURE )
    {
        return nullptr;
    }

    rndr::Texture::Type nativeType;
    switch ( type )
    {
        case aiTextureType_DIFFUSE:
            nativeType = rndr::Texture::Type::DIFFUSE;
            break;

        case aiTextureType_SPECULAR:
            nativeType = rndr::Texture::Type::SPECULAR;
            break;

        case aiTextureType_NORMALS:
            nativeType = rndr::Texture::Type::BUMP;
            break;

        default:
            // this should never happen (means the type is not supported)
            assert( false );
            return nullptr;
    }

    ResourceManager* resMgr = ResourceManager::inst();
    rndr::TexturePtr texture = resMgr->loadTexture( String( path.data ),
                                                    nativeType );

    return texture;
}

glm::vec3 MaterialFactory::getColor( const aiMaterial& material,
                                     const String& name,
                                     uint32 type, uint32 idx,
                                     const glm::vec3& defValue ) const
{
    aiColor3D color;
    glm::vec3 out;

    if ( material.Get( name.c_str(), type, idx, color ) == AI_SUCCESS )
    {
        out = glm::vec3( color.r, color.g, color.b );
    }
    else
    {
        out = defValue;
    }

    return out;
}

float MaterialFactory::getFloat( const aiMaterial& material, const String& name,
                                 uint32 type, uint32 idx, float defValue ) const
{
    float value;

    if ( !material.Get( name.c_str(), type, idx, value ) == AI_SUCCESS )
    {
        value = defValue;
    }

    return value;
}

} // End nspc res

} // End nspc demo