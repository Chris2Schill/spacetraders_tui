#pragma once

class IndexBuffer
{
    unsigned int rendererId_;
    unsigned int count_;

public:
    IndexBuffer() {}
    IndexBuffer(const unsigned int* data, unsigned int count);
    ~IndexBuffer();

    void bind() const;
    void unbind() const ;

    inline unsigned int getCount() const { return count_; }
};
