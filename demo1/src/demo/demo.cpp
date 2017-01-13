// demo.cpp
#include "demo.h"

namespace demo
{

bool Demo::startup()
{
    bool successful = rndr::GrApi::init();

    if ( !successful )
    {
        return false;
    }

    // set up window
    _window.setTitle( "Demo 1: Simple Blinn-Phong Renderer" );
    _window.open();
    _window.activate();
    printf( "OpenGL version is (%s)\n", glGetString( GL_VERSION ) );

    // create and compile shader
    _shader = rndr::Shader( "simple" );
    _shader.load();

    // prepare renderer
    _renderer.setRenderTarget( &_window );
    _renderer.setShader( &_shader );

    // set up camera
    _camera.setFarPlane( 100.0f );
    _camera.setNearPlane( -1.0f );
    _camera.setFieldOfView( 45.0f );
    _camera.transform().setPosition( glm::vec3( 0.0f, 0.0f, -5.0f ) );

    // load cube
    rndr::Model model( "res/models/cube.obj" );
    model.push( _shader );

    _cube.setModel( std::move( model ) );

    // prepare scene
    _scene.addObject( &_cube );

    return true;
}

void Demo::run()
{
    glEnable( GL_DEPTH_TEST );
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );

    // run while the window is open
    while ( _window.isOpen() )
    {
        glViewport( 0, 0, _window.width(), _window.height() );

        _renderer.render( _camera, _scene );

        glfwPollEvents();

        _window.swapBuffer();
        _window.update();
    }
}

void Demo::shutdown()
{
    rndr::GrApi::terminate();
}

} // End nspc demo