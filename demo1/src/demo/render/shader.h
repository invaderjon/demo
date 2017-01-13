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
#include "demo/strdef.h"

namespace demo
{

namespace rndr
{

class Shader
{
  private:
    // STRUCTURES
    /**
     * An OpenGL shader.
     */
    struct GlShader
    {
        /**
         * The shader filename.
         */
        String filename;

        /**
         * The shader type.
         */
        uint32 type;

        /**
         * The shader handle.
         */
        uint32 handle;
    };

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
     * The name of the shader set to use.
     */
    String _setName;

    /**
     * The id.
     */
    uint64 _id;

    /**
     * The OpenGL program handle.
     */
    uint32 _program;

    /**
     * The projection matrix attribute.
     */
    uint32 _matProjAttrib;

    /**
     * The view matrix attribute.
     */
    uint32 _matViewAttrib;

    /**
     * The model matrix attribute.
     */
    uint32 _matModelAttrib;

    /**
     * The normal matrix attribute.
     */
    uint32 _matNormAttrib;

    /**
     * The vertex position attribute.
     */
    uint32 _vertPosAttrib;

    /**
     * The vertex normal attribute.
     */
    uint32 _vertNormAttrib;

    // HELPER FUNCTIONS
    /**
     * Bind the OpenGL attributes.
     */
    void bindAttributes();
  
  public:
    // CONSTRUCTORS
    /**
     * Construct a shader.
     */
    Shader();

    /**
     * Construct a shader using the specified shader set.
     * @param name The name of the shader set to use.
     */
    Shader( const String& name );

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
     * Get the projection matrix attribute id.
     * @return The projection matrix attribute.
     */
    uint32 matProjectionAttr() const;

    /**
     * Get the view matrix attribute id.
     * @return The view matrix attribute.
     */
    uint32 matViewAttrib() const;

    /**
     * Get the model matrix attribute id.
     * @return The model matrix attribute.
     */
    uint32 matModelAttrib() const;

    /**
     * Get the normal matrix attribute id.
     * @return The normal matrix attribute.
     */
    uint32 matNormalAttrib() const;

    /**
     * Get the vertex position attribute id.
     * @return The vertex position attribute.
     */
    uint32 vertPositionAttrib() const;

    /**
     * Get the vertex normal attribute id.
     * @return The vertex normal attribute.
     */
    uint32 vertNormalAttrib() const;

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

    // MUTATOR FUNCTIONS
    /**
     * Set the shader set to use.
     * This only works if this is not loaded.
     * @param name The name of the shader set to use.
     */
    void setShaderSet( const String& name );

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
Shader::Shader() : _setName(), _id( ++g_nextId ), _program(), _vertPosAttrib(),
                   _vertNormAttrib()
{
}

inline
Shader::Shader( const String& name ) 
    : _setName( name ), _id( ++g_nextId ), _program(), _vertPosAttrib(),
      _vertNormAttrib()
{
}

inline
Shader::Shader( const Shader& other ) 
    : _setName( other._setName ), _id( other._id ), _program( other._program ),
      _vertPosAttrib( other._vertPosAttrib ),
      _vertNormAttrib( other._vertNormAttrib )
{
}

inline
Shader::~Shader()
{
    if ( isLoaded() )
    {
        release();
    }
}

// ACCESSOR FUNCTIONS
inline
uint64 Shader::id() const
{
    return _id;
}

inline
uint32 Shader::matProjectionAttr() const
{
    return _matProjAttrib;
}

inline
uint32 Shader::matViewAttrib() const
{
    return _matViewAttrib;
}

inline
uint32 Shader::matModelAttrib() const
{
    return _matModelAttrib;
}

inline
uint32 Shader::matNormalAttrib() const
{
    return _matNormAttrib;
}

inline
uint32 Shader::vertPositionAttrib() const
{
    return _vertPosAttrib;
}

inline
uint32 Shader::vertNormalAttrib() const
{
    return _vertNormAttrib;
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

// MUTATOR FUNCTIONS
inline
void Shader::setShaderSet( const String& name )
{
    _setName = name;
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