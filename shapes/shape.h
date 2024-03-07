#pragma once
#include "renderer/vertex_buffer.h"
#include "renderer/vertex_buffer_layout.h"
#include "renderer/vertex.h"

namespace Shapes
{

class Shape
{
public:
    std::shared_ptr<VertexArray> vertexArray;
    std::shared_ptr<VertexBufferLayout> layout;
    std::shared_ptr<VertexBuffer> vertexBuffer;
    std::shared_ptr<IndexBuffer> indexBuffer;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    Shape(std::shared_ptr<VertexArray> va,
        std::shared_ptr<VertexBuffer> vb,
        std::shared_ptr<VertexBufferLayout> vbl,
        std::shared_ptr<IndexBuffer> ib,
        std::vector<Vertex> vert,
        std::vector<unsigned int> ind)
        : vertexArray(va),
        vertexBuffer(vb),
        layout(vbl),
        indexBuffer(ib),
        vertices(vert),
        indices(ind)
    {}
};

}
