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
in vec2 vertTexCoord;

// constants
const vec3 lightPos = vec3( 0.0, 20.0, 20.0 );

// outputs
out vec3 vLightPos;
sample out vec3 vPosition;
sample out vec3 vNormal;
sample out vec3 vTangent;
sample out vec3 vBitangent;
sample out vec2 vTexCoord;

void main()
{
    vec4 position = matView * matModel * vec4( vertPosition, 1.0 );
    vec4 light = matView * vec4( lightPos, 1.0 );

    // HACK: Force left-handed tangents to make compatible with mirrored normal
    //       map.
    // TODO: find more elegant solution
    vec3 N = normalize( matNormal * vertNormal );;
    vec3 T = normalize( matNormal * vertTangent );
    vec3 B = normalize( matNormal * vertBitangent );
    if ( dot( cross( N, T ), B ) > 0.0 )
    {
        T = T * -1.0;
    }

    vNormal = N;
    vTangent = T;
    vBitangent = B;
    vPosition = vec3( position / position.w );
    vTexCoord = vertTexCoord;
    vLightPos = vec3( light / light.w );

    gl_Position = matProjection * matView * matModel *
            vec4( vertPosition, 1.0 );
}