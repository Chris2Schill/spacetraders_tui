#pragma once

#include <vector>
#include "gl_multiarch.h"

struct VertexBufferElement
{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int getSizeOfType(unsigned int type)
    {
        switch (type)
        {
            case GL_FLOAT: return 4;
            case GL_UNSIGNED_INT: return 4;
            case GL_UNSIGNED_BYTE: return 1;
        }

        ASSERT(false);

        return 0;
    }
};

class VertexBufferLayout
{
    std::vector<VertexBufferElement> elements_;
    unsigned int stride_;

public:
    VertexBufferLayout()
        : stride_(0) {}

    template<typename T>
    void push(unsigned int count)
    {
    //    static_assert(false);
    }

    inline const std::vector<VertexBufferElement> getElements() const { return elements_; }
    inline unsigned int getStride() const { return stride_; }
};

template<>
inline void VertexBufferLayout::push<float>(unsigned int count)
{
elements_.push_back( {GL_FLOAT, count, GL_FALSE } );
stride_ += count * VertexBufferElement::getSizeOfType(GL_FLOAT);
}

template<>
inline void VertexBufferLayout::push<unsigned int>(unsigned int count)
{
elements_.push_back( {GL_UNSIGNED_INT, count, GL_FALSE } );
stride_ += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT);
}

template<>
inline void VertexBufferLayout::push<unsigned char>(unsigned int count)
{
elements_.push_back( {GL_UNSIGNED_BYTE, count, GL_TRUE } );
stride_ += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE);
}

