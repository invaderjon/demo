// grapi.h
//
// Includes every required for the graphics api.
//
#ifndef DEMO_GRAPI_H
#define DEMO_GRAPI_H

// if on Windows with MinGW32 or MSVC
#if defined(__MINGW32__) || defined(_MSC_VER)

#define _GLEW_

#define GL_GLEXT_PROTOTYPES
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>

#else

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>

#endif

#include <GLFW/glfw3.h>

namespace demo
{

namespace rndr
{


struct GrApi
{
    // UTILITY FUNCTIONS
    /**
     * Initialize the graphics api.
     * This must be called before any graphics api can be used.
     * @return Was the api successfully initialized?
     */
    static bool init();

    /**
     * Unload the graphics api.
     * This should be called when finished.
     */
    static void terminate();
};

} // End nspc rndr

} // End nspc demo

#endif // DEMO_GRAPI_H