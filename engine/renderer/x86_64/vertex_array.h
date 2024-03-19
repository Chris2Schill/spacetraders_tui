#pragma once

#include <memory>
#include "../vertex_buffer.h"
#include "../index_buffer.h"

class VertexBufferLayout;

class VertexArray
{
    unsigned int rendererId_;

public:
    VertexArray();
    ~VertexArray();

    void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
    void addBuffer(const std::shared_ptr<VertexBuffer> vb, const std::shared_ptr<VertexBufferLayout> layout);
    void bind() const;
    void unbind() const;

    std::shared_ptr<IndexBuffer> getIndexBuffer() { return indexBuffer; }

private:
    std::shared_ptr<IndexBuffer> indexBuffer;
};

