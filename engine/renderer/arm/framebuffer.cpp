#include "renderer/arm/framebuffer.h"

#include "logger.h"

Framebuffer::Framebuffer(int width, int height)
    : width(width)
    , height(height)
{
    LOG(ERROR) << "Framebuffers not yet supported";
    // GL_CALL(glGenFramebuffers(1, &fb));
    // GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, fb));
    //
    // GL_CALL(glGenTextures(1, &color));
    // GL_CALL(glBindTexture(GL_TEXTURE_2D, color));
    //
    // GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    // GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    //
    // GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL));
    // GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
    // GL_CALL(glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color, 0));
    //
    // GL_CALL(glGenRenderbuffers(1, &depth));
    // GL_CALL(glBindRenderbuffer(GL_RENDERBUFFER, depth));
    // GL_CALL(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height));
    // GL_CALL(glBindRenderbuffer(GL_RENDERBUFFER, 0));
    // GL_CALL(glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depth));
    // GL_CALL(int ret = glCheckFramebufferStatus(GL_FRAMEBUFFER));
    // if (ret != GL_FRAMEBUFFER_COMPLETE)
    // {
    //     LOG(ERROR) << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    // }
    // unbind();
}

void Framebuffer::bind() const
{
    LOG(ERROR) << "Framebuffers not yet supported";
    // GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
    // GL_CALL(glEnable(GL_TEXTURE_2D));
    // GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, fb));
}

void Framebuffer::unbind() const
{
    LOG(ERROR) << "Framebuffers not yet supported";
    // GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
    // GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}
