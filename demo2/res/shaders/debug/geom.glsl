#version 400

// REFERENCE: http://sunandblackcat.com/tipFullView.php?l=eng&topicid=29&topic
//            =Geometry-Shader-Normals-Edges

// type of input primitives
layout( triangles ) in;

// display: normal, tangent, bittangent, and eddges
layout( line_strip, max_vertices = 24 ) out;

// the matrices
uniform mat4 matProjection;
uniform mat4 matView;
uniform mat4 matModel;
uniform mat3 matNormal;

// inputs
in vec3 vPosition[];
in vec3 vNormal[];
in vec3 vTangent[];
in vec3 vBitangent[];

// color to fragment shader
out vec4 colorDebug;

void main()
{
    mat4 projView = matProjection * matView;

    // normals of each vertex
    vec3 norm[3];
    norm[0] = vNormal[0].xyz;
    norm[1] = vNormal[1].xyz;
    norm[2] = vNormal[2].xyz;

    // adjust vert positions to avoid z fighting
    vec4 pos[3];
    pos[0] = projView * vec4( gl_in[0].gl_Position.xyz + norm[0] * 0.01, 1.0 );
    pos[1] = projView * vec4( gl_in[1].gl_Position.xyz + norm[1] * 0.01, 1.0 );
    pos[2] = projView * vec4( gl_in[2].gl_Position.xyz + norm[2] * 0.01, 1.0 );

    // output normals
    for ( int i = 0; i < gl_in.length(); ++i )
    {
        vec3 P = gl_in[i].gl_Position.xyz;

        // create normal for vert
        colorDebug = vec4( 0.0, 0.0, 1.0, 1.0 );
        gl_Position = pos[i];
        EmitVertex();
        gl_Position = projView * vec4( P + norm[i] * 0.2, 1.0 );
        EmitVertex();
        EndPrimitive();

        // create tangent for vertex
        colorDebug = vec4( 0.0, 1.0, 0.0, 1.0 );
        gl_Position = pos[i];
        EmitVertex();
        gl_Position = projView * vec4( P + vTangent[i].xyz * 0.2, 1.0 );
        EmitVertex();
        EndPrimitive();

        // create tangent for vertex
        colorDebug = vec4( 1.0, 0.0, 0.0, 1.0 );
        gl_Position = pos[i];
        EmitVertex();
        gl_Position = projView * vec4( P + vBitangent[i].xyz * 0.2, 1.0 );
        EmitVertex();
        EndPrimitive();
    }

    // create edges for triangle
    colorDebug = vec4( 0.25, 0.25, 0.25, 0.25 );
    gl_Position = pos[0];
    EmitVertex();
    gl_Position = pos[1];
    EmitVertex();
    gl_Position = pos[2];
    EmitVertex();
    gl_Position = pos[0];
    EmitVertex();
    EndPrimitive();
}