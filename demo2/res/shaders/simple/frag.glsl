#version 400

// inputs
in vec3 vLightPos;
sample in vec3 vPosition;
sample in vec3 vNormal;

const vec3 SPECULAR_COLOR = vec3( 1.0, 1.0, 1.0 );
const vec3 DIFFUSE_COLOR = vec3( 0.5, 0.5, 0.5 );
const vec3 AMBIENT = vec3( 0.1, 0.1, 0.1 );
const float SHININESS = 18.0;

void main()
{
    // compute directional vectors
    vec3 normal = normalize( vNormal );
    vec3 lightDir = normalize( vLightPos - vPosition );

    // compute lambertian (diffuse) light
    float lambertian = max( dot( lightDir, normal ), 0.0 );
    float specular = 0.0;

    // if lit then compute specular
    if ( lambertian > 0.0 )
    {
        vec3 viewDir = normalize( -vPosition );
        vec3 halfDir = normalize( lightDir + viewDir );
        float specAngle = max( dot( halfDir, normal ), 0.0 );

        specular = pow( specAngle, SHININESS );
    }

    // compute lighting
    vec3 diffuseLight = lambertian * DIFFUSE_COLOR;
    vec3 specularLight = specular * SPECULAR_COLOR;
    vec3 color = clamp( diffuseLight + specularLight + AMBIENT, 0.0, 1.0 );

    gl_FragColor = vec4( color, 1.0 );
}