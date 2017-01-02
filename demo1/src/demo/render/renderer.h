// renderer.h
//
// Draws scenes as they are observed by a specified camera.
//
// The renderer requires a render target which specifies where to draw the
// scene to. This can be a window or it can be a portion of one such as in
// the case of a split screen.
//
#ifndef DEMO_RENDERER_H
#define DEMO_RENDERER_H

#include "demo/object/camera.h"
#include "demo/object/scene.h"
#include "demo/render/irendertarget.h"
#include "demo/render/shader.h"

namespace demo
{

namespace rndr
{

class Renderer
{
  private:
    // MEMBERS
    /**
     * The shader set used to draw the scene.
     */
    Shader* _shader;

    /**
     * The render target that the renderer draws to.
     */
    IRenderTarget* _target;

  public:
    // CONSTRUCTORS
    /**
     * Construct a new renderer.
     */
    Renderer();

    /**
     * Construct a copy of a renderer.
     * @param other The other renderer.
     */
    Renderer( const Renderer& other );

    /**
     * Destruct the renderer.
     */
    ~Renderer();

    // OPERATORS
    /**
     * Assign this as a copy of a renderer.
     * @param other The other renderer.
     * @return This.
     */
    Renderer& operator=( const Renderer& other );

    // MUTATOR FUNCTIONS
    /**
     * Set the shader used to draw.
     * @param shader The shader.
     */
    void setShader( Shader* shader );

    /**
     * Set the render target.
     * @param target The render target.
     */
    void setRenderTarget( IRenderTarget* target );

    // MEMBER FUNCTIONS
    /**
     * Render the specified scene from the viewpoint of the specified camera.
     * @param camera The camera to use to render.
     * @param scene The scene to render.
     */
    void render( const obj::Camera& camera, const obj::Scene& scene );
};

// CONSTRUCTORS
inline
Renderer::Renderer() : _shader( nullptr ), _target( nullptr )
{
}

inline
Renderer::Renderer( const Renderer& other ) 
    : _shader( other._shader ), _target( other._target )
{
}

inline
Renderer::~Renderer()
{
}

// OPERATORS
inline
Renderer& Renderer::operator=( const Renderer& other )
{
    _shader = other._shader;
    _target = other._target;
    return *this;
}

// MUTATOR FUNCTIONS
inline
void Renderer::setShader( Shader* shader )
{
    _shader = shader;
}

inline
void Renderer::setRenderTarget( IRenderTarget* target )
{
    _target = target;
}

} // End nspc rndr

} // End nspc demo

#endif // DEMO_RENDERER_H
