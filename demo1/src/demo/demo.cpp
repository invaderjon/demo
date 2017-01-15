// demo.cpp
#include "demo.h"

#include <iostream>

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

	// set up GLEW (if necessary)
    #ifdef _GLEW_
	int32 output = glewInit();
	if (GLEW_OK != output)
	{
		std::cout << "ERROR: " << glewGetErrorString(output)
			<< std::endl;
		return false;
	}
	#endif

    // create and compile shader
    _shader = rndr::Shader( "simple" );
    _shader.load();

    // prepare renderer
    _renderer.setRenderTarget( &_window );
    _renderer.setShader( &_shader );

    // set up camera
    _camera.setFarPlane( 100.0f );
    _camera.setNearPlane( 0.01f );
    _camera.setFieldOfView( 45.0f );
    _camera.transform().lookAt( glm::vec3( 0, 0, 3 ),
                                glm::vec3( 0, 0, 0 ),
                                glm::vec3( 0, 1, 0 ) );

    // load cube
    rndr::Model model( "res/models/monkey.obj" );
    model.push( _shader );

    _cube.setModel( std::move( model ) );

    // prepare scene
    _scene.addObject( &_cube );

    return true;
}

void Demo::run()
{
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_CULL_FACE );

    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );

    // run while the window is open
    while ( _window.isOpen() )
    {
        glViewport( 0, 0, _window.width(), _window.height() );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        _renderer.render( _camera, _scene );

        int32 error = glGetError();
        if ( error != GL_NO_ERROR )
        {
            std::cout << error << std::endl;
        }

        _cube.transform().rotateEuler( 0, 0.01, 0 );

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