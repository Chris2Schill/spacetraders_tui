#pragma once

#include "gl_multiarch.h"

#if defined(__x86_64__)
#include "x86_64/framebuffer.h"
#include "x86_64/vertex_array.h"
#elif defined(__arm__)
#include "arm/framebuffer.h"
#include "arm/vertex_array.h"
#endif
#include "index_buffer.h"
#include "shader.h"
#include "vertex.h"
#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"
#include "camera.h"
#include "engine/core/base.h"

extern std::string OPENGL_VERSION;


struct Renderer {

    void clear();
    void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
    void drawTriangleStrip(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
    void drawTriangleFan(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
    void drawLines(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
    void drawLineStrip(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
    void beginDefiningStencil();
    void endDefiningStencil();
    void setStencilAsInclusionMask();
    void setStencilAsExclusionMask();
    void clearStencil();

    void pushStencilRegion();
    void endStencilRegion();
    void popStencilRegion();

    Shader& getBasicShader();
    Shader& getTextShader();
    Shader& getTextureShader();

    void pushFramebuffer(const Framebuffer*);
    void popFramebuffer();


    static void beginScene(Camera& camera);

    struct SceneData {
        glm::mat4 ViewProjectionMatrix;
        Ref<VertexArray> quads;
    };

    inline static SceneData s_SceneData;

    inline static const std::string RESOURCE_DIR = "/resources";
};
