#include "vertex_array.h"

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <EGL/egl.h>

// #include "vertex_buffer_layout.h"
// #include "renderer.h"

VertexArray::VertexArray()
{
    // GL_CALL(glGenVertexArrays(1, &rendererId_));
}

VertexArray::~VertexArray()
{
    // GL_CALL(glDeleteVertexArrays(1, &rendererId_));
}

void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{

    vertexBuffer_ = vb;
    layout_ = layout;

    // bind();
    // vb.bind();
    //
    // size_t offset = 0;
    //
    // const auto& elements = layout.getElements();
    // for (unsigned int i = 0; i < elements.size(); ++i)
    // {
    //     const auto& element = elements[i];
    //
    //     GL_CALL(glEnableVertexAttribArray(i));
    //     GL_CALL(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (void*)offset));
    //     offset += element.count * VertexBufferElement::getSizeOfType(element.type);
    // }
}

void VertexArray::addBuffer(const std::shared_ptr<VertexBuffer> vb, const std::shared_ptr<VertexBufferLayout> layout)
{
    addBuffer(*vb, *layout);
}

void VertexArray::bind() const
{
    // GL_CALL(glBindVertexArray(rendererId_));
    vertexBuffer_.bind();

    size_t offset = 0;

    const auto& elements = layout_.getElements();
    for (unsigned int i = 0; i < elements.size(); ++i)
    {
        const auto& element = elements[i];

        GL_CALL(glEnableVertexAttribArray(i));
        GL_CALL(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout_.getStride(), (void*)offset));
        offset += element.count * VertexBufferElement::getSizeOfType(element.type);
    }
}

void VertexArray::unbind() const
{
    // GL_CALL(glBindVertexArray(0));
}
