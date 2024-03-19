#pragma once

class Framebuffer
{
    unsigned int fb;
    unsigned int color;
    unsigned int depth;
    unsigned int stencil;

    int width;
    int height;

public:
    Framebuffer(int width, int height);
    void bind() const;
    void unbind() const;

    inline int getWidth() const { return width; }
    inline int getHeight() const { return height; }
    inline unsigned int getFramebuffer() const { return fb; }
    inline unsigned int getColorBuffer() const { return color; }
    inline unsigned int getDepthBuffer() const { return depth; }
    inline unsigned int getStencilBuffer() const { return stencil; }
};
