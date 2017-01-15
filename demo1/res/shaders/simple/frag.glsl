#version 400

// inputs
in vec3 vLightPos;
sample in vec3 vPosition;
sample in vec3 vNormal;

void main()
{
    vec3 normal = normalize( vNormal );
    vec3 lightDir = normalize( vLightPos - vPosition );

    float diff = clamp( max( dot( normal, lightDir ), 0.0 ) + 0.1, 0.0, 1.0 );

    gl_FragColor = vec4( diff, diff, diff, 1.0 );
}