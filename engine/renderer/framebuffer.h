#pragma once
#include "gl_multiarch.h"

class Framebuffer
{
    GLuint fb;
    GLuint color;
    GLuint depth;
    GLuint stencil;

    int width;
    int height;

public:
    Framebuffer(int width, int height);
    void bind() const;
    void unbind() const;

    inline int getWidth() const { return width; }
    inline int getHeight() const { return height; }
    inline GLuint getFramebuffer() const { return fb; }
    inline GLuint getColorBuffer() const { return color; }
    inline GLuint getDepthBuffer() const { return depth; }
    inline GLuint getStencilBuffer() const { return stencil; }
};
