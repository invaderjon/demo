// shader.h
//
// A set of shaders that a renderer uses to draw the world.
//
// For OpenGL this is equivalent to a program.
//
#ifndef DEMO_SHADER_H
#define DEMO_SHADER_H

#include "demo/intdef.h"
#include "demo/render/grapi.h"

namespace demo
{

namespace rndr
{

class Shader
{
  private:
    // GLOBALS
    /**
     * The active shader id.
     */
    static uint64 g_activeId;

    /**
     * The next id.
     */
    static uint64 g_nextId;

    // MEMBERS
    /**
     * The id.
     */
    uint64 _id;

    /**
     * The OpenGL program handle.
     */
    uint32 _program;
  
  public:
    // CONSTRUCTORS
    /**
     * Construct a shader.
     */
    Shader();

    /**
     * Construct a copy of the other shader.
     * @param other The other shader.
     */
    Shader( const Shader& other );

    /**
     * Destruct the shader.
     */
    ~Shader();

    // OPERATORS
    /**
     * Assign this as a copy of another shader.
     * @param other The other shader.
     */
    Shader& operator=( const Shader& other );

    // ACCESSOR FUNCTIONS
    /**
     * Get the id.
     * @return The id.
     */
    uint64 id() const;

    /**
     * Check if the shader is ready to be used.
     * @return Is loaded?
     */
    bool isLoaded() const;
    
    /**
     * Check if this is the active shader.
     * @return Is active?
     */
    bool isActive() const;

    // MEMBER FUNCTIONS
    /**
     * Make this the active shader for rendering.
     */
    void activate();

    /**
     * Load and prepare for usage.
     */
    void load();

    /**
     * Release the resources.
     */
    void release();
};

// CONSTRUCTORS
inline
Shader::Shader() : _id( ++g_nextId ), _program( 0 )
{
}

inline
Shader::Shader( const Shader& other ) 
    : _id( other._id ), _program( other._program )
{
}

inline
Shader::~Shader()
{
}

// OPERATORS
inline
Shader& Shader::operator=( const Shader& other )
{
    _id = other._id;
    _program = other._program;
    return *this;
}

// ACCESSOR FUNCTIONS
inline
uint64 Shader::id() const
{
    return _id;
}

inline
bool Shader::isLoaded() const
{
    return _program != 0;
}

inline
bool Shader::isActive() const
{
    return _id == g_activeId;
}

// MEMBER FUNCTIONS
inline
void Shader::activate()
{
    glUseProgram( _program );
    g_activeId = _id;
}

} // End nspc rndr

} // End nspc demo

#endif // DEMO_SHADER_H