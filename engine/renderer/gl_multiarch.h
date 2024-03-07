#pragma once

#if defined(__x86_64__)
    #include <GL/glew.h>

#elif defined(__arm__)
    #include <GLES2/gl2.h>
    #include <GLES2/gl2ext.h>
    #include <EGL/egl.h>

    // Warning: Geometry shaders might not be supported
    // In the case of the toradex they are not.
    #ifndef GL_GEOMETRY_SHADER
        #define GL_GEOMETRY_SHADER 0x8DD9
    #endif
#endif

#ifdef WIN32
    #define ASSERT(x) if (!(x)) __debugbreak();
#else
    #include <signal.h>
    #define ASSERT(x) if (!(x)) raise(SIGTRAP);
#endif

#define GL_CALL(x) GLClearError(); x; ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);
