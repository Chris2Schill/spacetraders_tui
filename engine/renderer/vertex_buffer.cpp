#include "vertex_buffer.h"
#include "renderer.h"

VertexBuffer::VertexBuffer()
    : rendererId_(0)
{}

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    GL_CALL(glGenBuffers(1, &rendererId_));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, rendererId_));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::VertexBuffer(const void* data, unsigned int size, unsigned int drawMode)
{
    GL_CALL(glGenBuffers(1, &rendererId_));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, rendererId_));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, data, drawMode));
}

VertexBuffer::~VertexBuffer()
{
    GL_CALL(glDeleteBuffers(1, &rendererId_));
}

void VertexBuffer::bind() const
{
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, rendererId_));
}

void VertexBuffer::unbind() const
{
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void VertexBuffer::update(const void* data, unsigned int size) const
{
    bind();
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}
