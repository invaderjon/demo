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

void main()
{
    // compute directional vectors
    vec3 normal = normalize( vNormal );
    vec3 lightDir = normalize( vLightPos - vPosition );

    // use bump map if available
    if ( ( valMatFlags & BUMP_MAP_FLAG ) != 0 )
    {
        // compute normal from bump map
        mat3 bumpTrans = mat3( normalize( vTangent ),
                               normalize( vBitangent ),
                               normalize( vNormal ) );

        vec3 bumpNormal = texture( texBump, vTexCoord ).rgb * 2.0 - 1.0;

        normal = normalize( bumpTrans * bumpNormal );;
    }

    // compute lambertian (diffuse) light
    float lambertian = max( dot( lightDir, normal ), 0.0 );
    float specular = 0.0;

    // if lit then compute specular
    if ( lambertian > 0.0 )
    {
        vec3 viewDir = normalize( -vPosition );
        vec3 halfDir = normalize( lightDir + viewDir );
        float specAngle = max( dot( halfDir, normal ), 0.0 );

        // use specular map if available
        if ( ( valMatFlags & SPECULAR_MAP_FLAG ) != 0 )
        {
            float sampleShininess = clamp( texture( texSpecular, vTexCoord ).r,
                                           0.001, 0.999 );
            specular = pow( specAngle, valShininess * ( 1.0 - sampleShininess ) );
        }
        else
        {
            specular = pow( specAngle, valShininess );
        }
    }

    // compute lighting
    vec2 texCoord = vTexCoord;
    vec3 diffuseLight = lambertian * colorDiffuse;
    vec3 specularLight = specular * colorSpecular;

    // consider texture if available
    if ( ( valMatFlags & DIFFUSE_MAP_FLAG ) != 0 )
    {
        diffuseLight *= texture( texDiffuse, vTexCoord ).rgb;
    }

    vec3 color = clamp( diffuseLight + specularLight + AMBIENT,
                        0.0, 1.0 );

    gl_FragColor = vec4( color, 1.0 );
}