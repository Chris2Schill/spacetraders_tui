#pragma once


class VertexBuffer
{
    unsigned int rendererId_;
    
public:
    VertexBuffer();
    VertexBuffer(const void* data, unsigned int size);
    VertexBuffer(const void* data, unsigned int size, unsigned int drawMode);
    ~VertexBuffer();

    void bind() const;
    void unbind() const;
    void update(const void* data, unsigned int size) const;
};
