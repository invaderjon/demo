// grapi.h
//
// Includes every required for the graphics api.
//
#ifndef DEMO_GRAPI_H
#define DEMO_GRAPI_H

// if on Windows with MinGW32 or MSVC
#if defined(__MINGW32__) || defined(_MSC_VER)

#include <GL/glew.h>

#else

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>

#endif

#endif // DEMO_GRAPI_H