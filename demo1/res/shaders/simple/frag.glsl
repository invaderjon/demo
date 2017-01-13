#version 400

sample in vec3 vPositionInterp;
sample in vec3 vNormalInterp;

// fixed color attributes
const vec3 lightPosition = vec3( 1.0, 1.0, 1.0 );
const vec3 lightAmbient = vec3( 0.1, 0.1, 0.1 );
const vec3 colorDiffuse = vec3( 0.5, 0.5, 0.5 );
const vec3 colorSpecular = vec3( 1.0, 1.0, 1.0 );
const float shininess = 16.0;
const float gamma = 2.2;

// blinn-phong shading model
void main()
{
    // compute preliminary values
    vec3 normal = normalize( vNormalInterp );
    vec3 lightDir = normalize( lightPosition - vPositionInterp );

    float lambertian = max( dot( lightDir, normal ), 0.0 );
    float specular = 0.0;

    // ensure object is being lit
    if ( lambertian > 0.0 )
    {
        vec3 viewDir = normalize( -vPositionInterp );

        vec3 halfDir = normalize( lightDir + viewDir );
        float specularAngle = max( dot( halfDir, normal ), 0.0 );
        specular = pow( specularAngle, shininess );
    }

    // compute color and apply gamma correction
    vec3 colorNoGamma = lightAmbient + lambertian * colorDiffuse +
            specular * colorSpecular;
    vec3 color = pow( colorNoGamma, vec3( 1.0 / gamma ) );

    gl_FragColor = vec4( 1.0, 1.0, 1.0, 1.0 );
}