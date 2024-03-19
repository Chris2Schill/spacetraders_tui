#include "uniform_buffer.h"

#include "renderer.h"

#include "engine/platform/opengl/opengl_uniform_buffer.h"

Ref<UniformBuffer> UniformBuffer::Create(uint32_t size, uint32_t binding)
{
    return create_ref<OpenGLUniformBuffer>(size, binding);
}
