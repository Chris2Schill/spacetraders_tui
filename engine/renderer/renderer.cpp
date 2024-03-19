#include "renderer.h"
#include <stack>
#include <iostream>
// #include "logger.h"

std::string OPENGL_VERSION = "#version 300 es\n";

std::stack<const Framebuffer*> framebufferStack;

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cerr << "[OpenGL Error] (" << error << "): " << function << " " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}

void Renderer::clear()
{
    GL_CALL(glStencilMask(0xFF));
    GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
    GL_CALL(glStencilMask(0x00));
}

void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)
{
    shader.bind();
    va.bind();
    ib.bind();

    GL_CALL(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::drawTriangleStrip(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)
{
    shader.bind();
    va.bind();
    ib.bind();

    GL_CALL(glDrawElements(GL_TRIANGLE_STRIP, ib.getCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::drawTriangleFan(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)
{
    shader.bind();
    va.bind();
    ib.bind();

    GL_CALL(glDrawElements(GL_TRIANGLE_FAN, ib.getCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::drawLines(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)
{
    shader.bind();
    va.bind();
    ib.bind();

    GL_CALL(glDrawElements(GL_LINES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::drawLineStrip(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)
{
    shader.bind();
    va.bind();
    ib.bind();

    GL_CALL(glDrawElements(GL_LINE_STRIP, ib.getCount(), GL_UNSIGNED_INT, nullptr));
}

int stencilRegionStackSize = 0;

void Renderer::beginDefiningStencil()
{
    GL_CALL(glEnable(GL_STENCIL_TEST));
    GL_CALL(glStencilMask(0xFF));
    GL_CALL(glStencilFunc(GL_ALWAYS, 1, 0xFF));
    GL_CALL(glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE));
}
void Renderer::endDefiningStencil()
{
    setStencilAsInclusionMask();
    GL_CALL(glStencilMask(0x00));
}
void Renderer::setStencilAsInclusionMask()
{
    GL_CALL(glStencilFunc(GL_EQUAL, 1, 0xFF));
}
void Renderer::setStencilAsExclusionMask()
{
    GL_CALL(glStencilFunc(GL_NOTEQUAL, 1, 0xFF));
}
void Renderer::clearStencil()
{
    GL_CALL(glStencilMask(0xFF));
    GL_CALL(glClear(GL_STENCIL_BUFFER_BIT));
    GL_CALL(glStencilMask(0x00));
    GL_CALL(glDisable(GL_STENCIL_TEST));
    stencilRegionStackSize = 0;
}

void Renderer::pushStencilRegion()
{
    stencilRegionStackSize++;
    GL_CALL(glEnable(GL_STENCIL_TEST));
    GL_CALL(glStencilMask(0xFF));
    GL_CALL(glStencilFunc(GL_ALWAYS, stencilRegionStackSize, 0xFF));
    GL_CALL(glStencilOp(GL_KEEP, GL_INCR, GL_INCR));
    GL_CALL(glDepthMask(GL_FALSE));
}
void Renderer::endStencilRegion()
{
    GL_CALL(glStencilFunc(GL_EQUAL, stencilRegionStackSize, 0xFF));
    GL_CALL(glStencilMask(0x00));
    // GL_CALL(glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP));
}

void Renderer::popStencilRegion()
{
    stencilRegionStackSize--;
    GL_CALL(glEnable(GL_STENCIL_TEST));
    GL_CALL(glStencilMask(0xFF));
    GL_CALL(glStencilFunc(GL_ALWAYS, stencilRegionStackSize, 0xFF));
    GL_CALL(glStencilOp(GL_KEEP, GL_DECR, GL_DECR));
}

Shader& Renderer::getBasicShader()
{
    static Shader shader = Shader::create(OPENGL_VERSION)
        .vertexShader("basic_vertex_3d.shader")
        .fragmentShader("basic_fragment_3d.shader")
        .build();

    return shader;
}

Shader& Renderer::getTextShader()
{
    static Shader shader = Shader::create(OPENGL_VERSION)
        .vertexShader("freetype_vertex.shader")
        .fragmentShader("freetype_fragment.shader")
        .build();

    return shader;
}

Shader& Renderer::getTextureShader()
{
    static Shader shader = Shader::create(OPENGL_VERSION)
        .vertexShader("textured_rect_vertex.shader")
        .fragmentShader("textured_rect_fragment.shader")
        .build();

    return shader;
}


void Renderer::pushFramebuffer(const Framebuffer* fb)
{
    fb->bind();
    framebufferStack.push(fb);
}

void Renderer::popFramebuffer()
{
    framebufferStack.pop();
    if (!framebufferStack.empty())
    {
        const Framebuffer* fb = framebufferStack.top();
        fb->bind();
    }
    else { GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, 0)); }
}

void Renderer::beginScene(Camera& camera)
{
}
