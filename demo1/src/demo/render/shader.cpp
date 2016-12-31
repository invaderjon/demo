// shader.cpp
#include "shader.h"

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
    // todo: load and link the shader program
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

} // End nspc rndr

} // End nspc demo