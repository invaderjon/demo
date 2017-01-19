#version 400

// the matrices
uniform mat4 matProjection;
uniform mat4 matView;
uniform mat4 matModel;
uniform mat3 matNormal;

// the vertex attributes
in vec3 vertPosition;
in vec3 vertNormal;

// constants
const vec3 lightPos = vec3( 0.0, 0.0, 5.0 );

// outputs
out vec3 vLightPos;
sample out vec3 vPosition;
sample out vec3 vNormal;

void main()
{
    vec4 position = matView * matModel * vec4( vertPosition, 1.0 );
    vec4 light = matView * vec4( lightPos, 1.0 );

    vNormal = normalize( matNormal * vertNormal );
    vPosition = vec3( position / position.w );
    vLightPos = vec3( light / light.w );

    gl_Position = matProjection * matView * matModel *
            vec4( vertPosition, 1.0 );
}