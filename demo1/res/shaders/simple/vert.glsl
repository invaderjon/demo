#version 400

// the matrices
uniform mat4 matProjection;
uniform mat4 matView;
uniform mat4 matModel;
uniform mat4 matNormal;

// the vertex attributes
in vec3 vertPosition;
in vec3 vertNormal;

// outputs
sample out vec3 vPositionInterp;
sample out vec3 vNormalInterp;

void main()
{
    // compute position
    vec4 position = matView * matModel * vec4( vertPosition, 1.0 );

    // outputs
    vPositionInterp = vec3( position ) / position.w;
    vNormalInterp = vec3( matNormal * vec4( vertNormal, 0.0 ) );

    // camera space position
    gl_Position = matProjection * position;
}