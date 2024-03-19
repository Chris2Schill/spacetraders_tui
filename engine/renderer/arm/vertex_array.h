#pragma once

#include <memory>
#include "renderer/vertex_buffer.h"
#include "renderer/vertex_buffer_layout.h"

// class VertexBufferLayout;

class VertexArray
{
    // unsigned int rendererId_;
    VertexBuffer vertexBuffer_;
    VertexBufferLayout layout_;

public:
    VertexArray();
    ~VertexArray();

    void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
    void addBuffer(const std::shared_ptr<VertexBuffer> vb, const std::shared_ptr<VertexBufferLayout> layout);
    void bind() const;
    void unbind() const;
};

