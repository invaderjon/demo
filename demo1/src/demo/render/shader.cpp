// shader.cpp
#include "shader.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <vector>

#include "demo/container/fixed_array.h"

namespace demo
{

namespace rndr
{

// GLOBALS
uint64 Shader::g_activeId = 0L;
uint64 Shader::g_nextId = 0L;

// MEMBER FUNCTIONS
void Shader::load()
{
    // stop if loaded
    if ( isLoaded() )
    {
        return;
    }

    // create array of shaders
    cntr::FixedArray<GlShader> shaders( 6 );
    for ( uint32 i = 0; i < 6; ++i )
    {
        shaders.push( GlShader() );
    }

    // populate shader structures
    shaders[0].filename = "res/shaders/" + _setName + "/vert.glsl";
    shaders[0].type = GL_VERTEX_SHADER;

    shaders[1].filename = "res/shaders/" + _setName + "/tesc.glsl";
    shaders[1].type = GL_TESS_CONTROL_SHADER;

    shaders[2].filename = "res/shaders/" + _setName + "/tese.glsl";
    shaders[2].type = GL_TESS_EVALUATION_SHADER;

    shaders[3].filename = "res/shaders/" + _setName + "/geom.glsl";
    shaders[3].type = GL_GEOMETRY_SHADER;

    shaders[4].filename = "res/shaders/" + _setName + "/frag.glsl";
    shaders[4].type = GL_FRAGMENT_SHADER;

    shaders[5].filename = "res/shaders/" + _setName + "/comp.glsl";
    shaders[5].type = GL_COMPUTE_SHADER;

    // compile shaders
    for ( int32 i = 0; i < shaders.size(); ++i )
    {
        std::ifstream file( shaders[i].filename, std::ios::in );

        // shader of that type doesn't exist so ignore it
        if ( !file )
        {
            shaders.removeAt(static_cast<uint32>( i-- ) );
            continue;
        }

        // read file
        std::stringstream buffer;
        String line;
        while ( !file.eof() )
        {
            getline( file, line );
            buffer << line << "\n";
        }

        String content = buffer.str();
        auto contentPtr = content.c_str();

        // compile shader
        shaders[i].handle = glCreateShader( shaders[i].type );
        uint32 handle = shaders[i].handle;

        glShaderSource( handle, 1, &contentPtr, nullptr );
        glCompileShader( handle );

        // check compilation result
        int32 success = GL_FALSE;
        int32 logLength;
        glGetShaderiv( handle, GL_COMPILE_STATUS, &success );
        if ( success == GL_FALSE )
        {
            // display error
            glGetShaderiv( handle, GL_INFO_LOG_LENGTH, &logLength );
            logLength = std::max( logLength, 1 );

            std::vector<GLchar> error( static_cast<uint32>( logLength ) );

            glGetShaderInfoLog( handle, logLength, nullptr, &error[0] );

            std::cout << "Failed to compile " << shaders[i].filename <<
                std::endl;
            std::cout << &error[0] << std::endl;

            // release resources and remove from list
            glDeleteShader( handle );
            shaders.removeAt( static_cast<uint32>( i-- ) );
            continue;
        }
    }
    
    // create program and attach shaders (also delete shaders)
    uint32 program = glCreateProgram();
    for ( int32 i = 0; i < shaders.size(); ++i )
    {
        glAttachShader( program, shaders[i].handle );
        glDeleteShader( shaders[i].handle );
    }

    // link the program
    glLinkProgram( program );

    // check result
    int32 success = GL_FALSE;
    int32 logLength;
    glGetProgramiv( program, GL_LINK_STATUS, &success );
    if ( success == GL_FALSE )
    {
        // display error
        glGetProgramiv( program, GL_INFO_LOG_LENGTH, &logLength );
        logLength = std::max( logLength, 1 );

        std::vector<GLchar> error( static_cast<uint32>( logLength ) );
        glGetProgramInfoLog( program, logLength, nullptr, &error[0] );

        std::cout << "Failed to link " << _setName << std::endl;
        std::cout << &error[0] << std::endl;

        // release resources and delete program
        glDeleteProgram( program );
        return;
    }

    // detach shaders
    for ( uint32 i = 0; i < shaders.size(); ++i )
    {
        glDetachShader( program, shaders[i].handle );
    }

    // store program and bind attributes
    _program = program;
    bindAttributes();
}

void Shader::release()
{
    if ( isActive() )
    {
        g_activeId = 0;
    }

    glDeleteProgram( _program );
    _program = 0;
}

// HELPER FUNCTIONS
void Shader::bindAttributes()
{
    // todo: bind attributes
}

} // End nspc rndr

} // End nspc demo