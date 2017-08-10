#version 400

// inputs
in vec3 vLightPos;
sample in vec3 vPosition;
sample in vec3 vNormal;
sample in vec3 vTangent;
sample in vec3 vBitangent;
sample in vec2 vTexCoord;

// material values
uniform vec3 colorDiffuse;
uniform vec3 colorSpecular;
uniform vec3 colorAmbient;
uniform float valShininess;
uniform uint valMatFlags;

// material textures
uniform sampler2D texDiffuse;
uniform sampler2D texSpecular;
uniform sampler2D texBump;

// constants
const vec3 AMBIENT = vec3( 0.1, 0.1, 0.1 );
const uint DIFFUSE_MAP_FLAG = 0x1;
const uint SPECULAR_MAP_FLAG = 0x2;
const uint BUMP_MAP_FLAG = 0x4;

// Get the normal vector.
vec3 getNormal()
{
    vec3 normal;

    if ( ( valMatFlags & BUMP_MAP_FLAG ) != 0 )
    {
        // compute normal from bump map
        mat3 bumpTrans = mat3( normalize( vTangent ),
                               normalize( vBitangent ),
                               normalize( vNormal ) );

        vec3 bumpNormal = texture( texBump, vTexCoord ).rgb;

        normal = normalize( bumpTrans * bumpNormal );
    }
    else
    {
        normal = normalize( vNormal );
    }

    return normal;
}

// Get the diffuse color.
vec3 getDiffuseColor()
{
    vec3 color = colorDiffuse;

    if ( ( valMatFlags & DIFFUSE_MAP_FLAG ) != 0 )
    {
        color = texture( texDiffuse, vTexCoord ).rgb;
    }

    return color;
}

// Get the specular color (alpha component is shininess).
vec4 getSpecularColor()
{
    vec4 color;

    // use specular map if available
    if ( ( valMatFlags & SPECULAR_MAP_FLAG ) != 0 )
    {
        color = texture( texSpecular, vTexCoord ).rgba;
        color.a *= 255.0;
    }
    else
    {
        color = vec4( colorSpecular, valShininess );
    }

    return color;
}

// Compute the specular lighting.
vec3 computeSpecular( vec4 color, vec3 normal, vec3 lightDir,
                      float lambertian )
{
    float specular = 0.0;

    if ( lambertian > 0.0 )
    {
        vec3 viewDir = normalize( -vPosition );
        vec3 halfDir = normalize( lightDir + viewDir );
        float specAngle = max( dot( halfDir, normal ), 0.0 );

        specular = pow( specAngle, color.a );
    }

    return specular * color.rgb;
}

void main()
{
    // get values required for light computation
    vec3 normal = getNormal();
    vec3 lightDir = normalize( vLightPos - vPosition );
    vec3 diffColor = getDiffuseColor();
    vec4 specColor = getSpecularColor();
    float lambertian = max( dot( lightDir, normal ), 0.0 );

    // compute lighting
    vec3 diffuseLight = lambertian * diffColor;
    vec3 specularLight = computeSpecular( specColor, normal, lightDir,
                                          lambertian );

    vec4 color = vec4( clamp( diffuseLight + specularLight + AMBIENT,
                              0.0, 1.0 ), 1.0 );

    gl_FragColor = color;
}