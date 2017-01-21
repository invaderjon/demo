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

    // CONSTANTS
    /**
     * The shader resource path.
     */
    static const String SHADER_PATH;

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
    uint32 _matProjAttr;

    /**
     * The view matrix attribute.
     */
    uint32 _matViewAttr;

    /**
     * The model matrix attribute.
     */
    uint32 _matModelAttr;

    /**
     * The normal matrix attribute.
     */
    uint32 _matNormAttr;

    /**
     * The vertex position attribute.
     */
    uint32 _vertPosAttr;

    /**
     * The vertex normal attribute.
     */
    uint32 _vertNormAttr;

    /**
     * The vertex tangent attribute.
     */
    uint32 _vertTangAttr;

    /**
     * The vertex texture coordinate attribute.
     */
    uint32 _vertTexCoordAttr;

    /**
     * The mesh diffuse color.
     */
    uint32 _colorDiffuse;

    /**
     * The mesh specular color.
     */
    uint32 _colorSpecular;

    /**
     * The mesh ambient color.
     */
    uint32 _colorAmbient;

    /**
     * The mesh shininess.
     */
    uint32 _valShininess;

    /**
     * The material flags.
     */
    uint32 _valMatFlags;

    // HELPER FUNCTIONS
    /**
     * Bind the OpenGL attributes.
     */
    void bindAttributes();
  
  public:
    // CONSTANTS
    /**
     * The diffuse map binding number.
     */
    static constexpr uint32 TEXTURE_INT_DIFFUSE = 0;

    /**
     * The specular map binding number.
     */
    static constexpr uint32 TEXTURE_INT_SPECULAR = 1;

    /**
     * The bump map binding number.
     */
    static constexpr uint32 TEXTURE_INT_BUMP = 2;

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
    uint32 matViewAttr() const;

    /**
     * Get the model matrix attribute id.
     * @return The model matrix attribute.
     */
    uint32 matModelAttr() const;

    /**
     * Get the normal matrix attribute id.
     * @return The normal matrix attribute.
     */
    uint32 matNormalAttr() const;

    /**
     * Get the vertex position attribute id.
     * @return The vertex position attribute.
     */
    uint32 vertPositionAttr() const;

    /**
     * Get the vertex normal attribute id.
     * @return The vertex normal attribute.
     */
    uint32 vertNormalAttr() const;

    /**
     * Get the vertex tangent attribute id.
     * @return The vertex tangent attribute.
     */
    uint32 vertTangentAttr() const;

    /**
     * Get the vertex UV map attribute id.
     * @return The vertex UV map attribute.
     */
    uint32 vertTexCoordAttr() const;

    /**
     * Get the diffuse color attribute id.
     * @return The diffuse color attribute.
     */
    uint32 colorDiffuse() const;

    /**
     * Get the specular color attribute id.
     * @return The specular color attribute.
     */
    uint32 colorSpecular() const;

    /**
     * Get the ambient color attribute id.
     * @return The ambient color attribute.
     */
    uint32 colorAmbient() const;

    /**
     * Get the shininess attribute id.
     * @return The shininess attribute.
     */
    uint32 valShininess() const;

    /**
     * Get the material flags attribute id.
     * @return The material flags attribute.
     */
    uint32 valMatFlags() const;

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
Shader::Shader() : _setName(), _id( ++g_nextId ), _program(), _matProjAttr(),
                   _matViewAttr(), _matModelAttr(), _matNormAttr(),
                   _vertPosAttr(), _vertNormAttr(), _vertTangAttr(),
                   _vertTexCoordAttr(), _colorDiffuse(), _colorSpecular(),
                   _colorAmbient(), _valShininess(), _valMatFlags()
{
}

inline
Shader::Shader( const String& name ) 
    : _setName( name ), _id( ++g_nextId ), _program(), _matProjAttr(),
      _matViewAttr(), _matModelAttr(), _matNormAttr(),
      _vertPosAttr(), _vertNormAttr(), _vertTangAttr(),
      _vertTexCoordAttr(), _colorDiffuse(), _colorSpecular(), _colorAmbient(),
      _valShininess(), _valMatFlags()
{
}

inline
Shader::Shader( const Shader& other ) 
    : _setName( other._setName ), _id( other._id ), _program( other._program ),
      _matProjAttr( other._matProjAttr ),
      _matViewAttr( other._matViewAttr ),
      _matNormAttr( other._matNormAttr ),
      _vertPosAttr( other._vertPosAttr ),
      _vertNormAttr( other._vertNormAttr ),
      _vertTangAttr( other._vertTangAttr ),
      _vertTexCoordAttr( other._vertTexCoordAttr ),
      _colorDiffuse( other._colorDiffuse ),
      _colorSpecular( other._colorSpecular ),
      _colorAmbient( other._colorAmbient ),
      _valShininess( other._valShininess ),
      _valMatFlags( other._valMatFlags )
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
    return _matProjAttr;
}

inline
uint32 Shader::matViewAttr() const
{
    return _matViewAttr;
}

inline
uint32 Shader::matModelAttr() const
{
    return _matModelAttr;
}

inline
uint32 Shader::matNormalAttr() const
{
    return _matNormAttr;
}

inline
uint32 Shader::vertPositionAttr() const
{
    return _vertPosAttr;
}

inline
uint32 Shader::vertNormalAttr() const
{
    return _vertNormAttr;
}

inline
uint32 Shader::vertTangentAttr() const
{
    return _vertTangAttr;
}

inline
uint32 Shader::vertTexCoordAttr() const
{
    return _vertTexCoordAttr;
}

inline
uint32 Shader::colorDiffuse() const
{
    return _colorDiffuse;
}

inline
uint32 Shader::colorSpecular() const
{
    return _colorSpecular;
}

inline
uint32 Shader::colorAmbient() const
{
    return _colorAmbient;
}

inline
uint32 Shader::valShininess() const
{
    return _valShininess;
}

inline
uint32 Shader::valMatFlags() const
{
    return _valMatFlags;
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