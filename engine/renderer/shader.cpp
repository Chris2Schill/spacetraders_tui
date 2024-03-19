
#include "shader.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include "renderer.h"
// #include "logger.h"
#include "util.h"

#define LOG(x) std::cerr


unsigned int Shader::currentRendererId_ = 0;

Shader::Builder::Builder(const std::string& glslVersion)
    : glslVersion_(glslVersion)
{}

Shader::Builder& Shader::Builder::vertexShader(const std::string filename)
{
    vertexShaders_.push_back(ShaderFile(GL_VERTEX_SHADER, Renderer::RESOURCE_DIR+std::string("/shaders/")+filename));
    return *this;
}

Shader::Builder& Shader::Builder::geometryShader(const std::string filename)
{
    geometryShaders_.push_back(ShaderFile(GL_GEOMETRY_SHADER, Renderer::RESOURCE_DIR+std::string("/shaders/")+filename));
    return *this;
}

Shader::Builder& Shader::Builder::fragmentShader(const std::string filename)
{
    fragmentShaders_.push_back(ShaderFile(GL_FRAGMENT_SHADER, Renderer::RESOURCE_DIR+std::string("/shaders/")+filename));
    return *this;
}

Shader Shader::Builder::build()
{
    Shader program(glCreateProgram());

    unsigned int rendererId = program.getRendererId();

    if (vertexShaders_.size()   > 0) { GL_CALL(glAttachShader(rendererId, compileShaders(vertexShaders_)));   }
    if (geometryShaders_.size() > 0) { GL_CALL(glAttachShader(rendererId, compileShaders(geometryShaders_))); }
    if (fragmentShaders_.size() > 0) { GL_CALL(glAttachShader(rendererId, compileShaders(fragmentShaders_))); }

    link(program);

    return program;
}

unsigned int Shader::Builder::compileShaders(std::vector<ShaderFile>& shaders)
{
    int shaderType = 0;

    // Gather source code into one vector
    std::vector<std::string> shaderSrcs;
    shaderSrcs.push_back((glslVersion_ + '\n'));
    shaderSrcs.push_back("#ifdef GL_ES\nprecision mediump float;\n#endif\n");
    for (unsigned i = shaders.size(); i-- > 0;)
    {
        ShaderFile& shader = shaders[i];
        shaderType = shader.type;
        std::string source = util::readSourceFile(shader.filepath);
        if (source.empty())
        {
            LOG(ERROR) << "[" __FILE__ << ":" << __LINE__ << "] "
                      << "[" << __FUNCTION__ << "]: "
                      << "error - failed to compile shader " << shader.filepath << std::endl;
        }
        shaderSrcs.push_back(source);
    }

    // Convert to char** for opengl interface
    std::vector<const char*> shaderPtrs;
    for (auto& code : shaderSrcs)
    {
        shaderPtrs.push_back(code.c_str());
    }

    unsigned int shaderId = compileShader(shaderType, shaderPtrs);
    if (shaderId == 0)
    {
        std::stringstream ss;
        ss << "    error in shader comprised of the files: ["
                   << shaders[0].filepath;

        for (unsigned i = 1; i < shaders.size(); ++i)
        {
             ss << ", " << shaders[i].filepath;
        }
        ss << "]\n";
        LOG(ERROR) << ss.str();
    }

    return shaderId;
}

std::string shadertype_to_string(const int type)
{
    switch (type)
    {
        case GL_VERTEX_SHADER:
            return "vertex";
        case GL_FRAGMENT_SHADER:
            return "fragment";
        case GL_GEOMETRY_SHADER:
            return "geometry";
        default:
            return "unknown";
    }

}

unsigned int Shader::Builder::compileShader(unsigned int type, std::vector<const char*>& sources)
{
    GL_CALL(unsigned int id = glCreateShader(type));
    GL_CALL(glShaderSource(id, sources.size(), sources.data(), nullptr));
    GL_CALL(glCompileShader(id));


    int result;
    GL_CALL(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (!result)
    {
        int length;
        GL_CALL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        std::vector<char> message(length);
        GL_CALL(glGetShaderInfoLog(id, length, &length, &message[0]));
        LOG(ERROR) << "Failed to compile " << shadertype_to_string(type) << " shader!\n"
                   << "\t" << &message[0];

        GL_CALL(glDeleteShader(id));

        return 0;
    }

    return id;
}

void Shader::Builder::link(Shader& program)
{
    unsigned int rendererId = program.getRendererId();
    GL_CALL(glLinkProgram(rendererId));
    GL_CALL(glValidateProgram(rendererId));
}


Shader::Shader()
{
}
Shader::Shader(unsigned int rendererId)
    : rendererId_(rendererId)
{
}

Shader::~Shader()
{}

void Shader::bind() const
{
    if (currentRendererId_ != rendererId_)
    {
        GL_CALL(glUseProgram(rendererId_));
        currentRendererId_ = rendererId_;
    }
}

void Shader::unbind() const
{
    GL_CALL(glUseProgram(0));
}

void Shader::destroy() const
{
    GL_CALL(glDeleteProgram(rendererId_));
}

void Shader::setUniform1i(const std::string& name, int v0)
{
    GL_CALL(glUniform1i(getUniformLocation(name), v0));
}

void Shader::setUniform1f(const std::string& name, float v0)
{
    GL_CALL(glUniform1f(getUniformLocation(name), v0));
}

void Shader::setUniform2f(const std::string& name, float v0, float v1)
{
    GL_CALL(glUniform2f(getUniformLocation(name), v0, v1));
}

void Shader::setUniform3f(const std::string& name, float v0, float v1, float v2)
{
    GL_CALL(glUniform3f(getUniformLocation(name), v0, v1, v2));
}

void Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    GL_CALL(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
}

void Shader::setUniformMatrix3fv(const std::string& name, glm::mat3& matrix)
{
    GL_CALL(glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

void Shader::setUniformMatrix4fv(const std::string& name, glm::mat4& matrix)
{
    GL_CALL(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

unsigned int Shader::getRendererId()
{
    return rendererId_;
}

unsigned int Shader::getUniformLocation(const std::string& name)
{
    auto iter = uniformLocationCache_.find(name);
    if (iter == uniformLocationCache_.end())
    {
        GL_CALL(int location = glGetUniformLocation(rendererId_, name.c_str()));
        if (location == -1) { LOG(WARNING) << "Warning: uniform '" << name << "' doesn't exist!"; }
        uniformLocationCache_.insert({ name, location });
        return location;
    }

    return uniformLocationCache_[name];
}


