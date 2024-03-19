#pragma once

#include <renderer/renderer.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace Drawables
{

class Drawable
{
public:
    std::shared_ptr<VertexArray> vertexArray;
    std::shared_ptr<VertexBuffer> vertexBuffer;
    std::shared_ptr<VertexBufferLayout> layout;
    std::shared_ptr<IndexBuffer> indexBuffer;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    glm::vec3 position;

    Drawable(glm::vec3 pos) : position(pos) {}

    Drawable(std::shared_ptr<VertexArray> va,
        std::shared_ptr<VertexBuffer> vb,
        std::shared_ptr<VertexBufferLayout> vbl,
        std::shared_ptr<IndexBuffer> ib,
        std::vector<Vertex> vert,
        std::vector<unsigned int> ind,
        glm::vec3 pos)
        : vertexArray(va),
        vertexBuffer(vb),
        layout(vbl),
        indexBuffer(ib),
        vertices(vert),
        indices(ind),
        position(pos)
    {}

    glm::mat4 getRotationMatrix(float deg)
    {
        auto rotation =  glm::translate(glm::mat4(1), position) * // back to position
                         glm::rotate(glm::mat4(1), glm::radians(deg), glm::vec3(0.0f,0.0f,-1.0f)) * // rotate
                         glm::translate(glm::mat4(1), -position); // to center
        return rotation;
    }

    void rotate2D(float deg)
    {
        for (auto& vert : vertices)
        {
            auto rotation =  glm::translate(glm::mat4(1), position) * // back to position
                             glm::rotate(glm::mat4(1), glm::radians(deg), glm::vec3(0.0f,0.0f,-1.0f)) * // rotate
                             glm::translate(glm::mat4(1), -position); // to center


            vert.position = rotation * glm::vec4(vert.position, 1.0);

        }
        updateVertexBuffer();
    }

    void scale(glm::vec3 scale)
    {
        for (auto& vert : vertices)
        {
            auto rotation =  glm::translate(glm::mat4(1), position) * // back to position
                             glm::scale(glm::mat4(1), scale) * // scale
                             glm::translate(glm::mat4(1), -position); // to center


            vert.position = rotation * glm::vec4(vert.position, 1.0);

        }
        updateVertexBuffer();
    }

    void setAlpha(float alpha)
    {
        for (auto& vert : vertices)
        {
            vert.color.a = alpha;
        }
        updateVertexBuffer();
    }

    void setColor(glm::vec4 color)
    {
        for (auto& vert : vertices)
        {
            vert.color = color;
        }

        updateVertexBuffer();
    }
    
    void updateVertexBuffer()
    {
        vertexBuffer->update(&vertices[0], vertices.size() * sizeof(Vertex));
    }
    void updateIndexBuffer()
    {
        indexBuffer->update(&indices[0], indices.size());
    }
};

}
