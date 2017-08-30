#version 400

// the matrices
uniform mat4 matProjection;
uniform mat4 matView;
uniform mat4 matModel;
uniform mat3 matNormal;

// the vertex attributes
in vec3 vertPosition;
in vec3 vertNormal;
in vec3 vertTangent;
in vec3 vertBitangent;

// outputs
out vec3 vPosition;
out vec3 vNormal;
out vec3 vTangent;
out vec3 vBitangent;

void main()
{
    vec4 position = matView * matModel * vec4( vertPosition, 1.0 );

    vNormal = normalize( matNormal * vertNormal );
    vTangent = normalize( matNormal * vertTangent );
    vBitangent = normalize( matNormal * vertBitangent );
    vPosition = vec3( position / position.w );

    gl_Position = matModel * vec4( vertPosition, 1.0 );
}