// demo.cpp
#include "demo.h"

#include <iostream>

#include "demo/resource/resource_manager.h"

namespace demo
{

bool Demo::startup()
{
    // start up subsystems
    bool successful = rndr::GrApi::startup();
    res::ResourceManager::startup();

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
    _camera.transform().lookAt( glm::vec3( 0, 0, 5 ),
                                glm::vec3( 0, 0, 0 ),
                                glm::vec3( 0, 1, 0 ) );

    // load resources
    res::ResourceManager* resMgr = res::ResourceManager::inst();

    rndr::ModelPtr model = resMgr->loadModel( "models/box.obj" );
    model->push( _shader );

    _model.setModel( std::move( model ) );

    // prepare scene
    _scene.addObject( &_model );

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

        checkForGlErrors();

        _model.transform().rotateEuler( 0, 0.01, 0 );

        glfwPollEvents();
        _window.swapBuffer();
        _window.update();
    }
}

void Demo::shutdown()
{
    _model.setModel( nullptr );
    res::ResourceManager::shutdown();
    rndr::GrApi::shutdown();
}

// HELPER FUNCTIONS
void Demo::checkForGlErrors() const
{
    int32 error = glGetError();
    if ( error != GL_NO_ERROR )
    {
        std::cout << error << std::endl;
    }
}

} // End nspc demo