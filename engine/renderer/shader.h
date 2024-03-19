#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include <vector>
#include <glm/ext/matrix_float4x4.hpp>

extern const std::string SHADER_DIR;

class Shader
{
    static unsigned int currentRendererId_;

public:
    struct ShaderFile
    {
        const int type;
        const std::string filepath;
        ShaderFile(const int shaderType, const std::string shaderFilepath)
            : type(shaderType),
            filepath(shaderFilepath)
        {}
    };

    class Builder
    {
    public:
        Builder(const std::string& glslVersion);
        Builder& vertexShader(const std::string filename);
        Builder& geometryShader(const std::string filename);
        Builder& fragmentShader(const std::string filename);
        Shader build();


    private:

        unsigned int compileShaders(std::vector<ShaderFile>& shaders);
        unsigned int compileShader(unsigned int type, std::vector<const char*>& sources);
        void link(Shader& program);

        const std::string glslVersion_;

        std::vector<ShaderFile> vertexShaders_;
        std::vector<ShaderFile> fragmentShaders_;
        std::vector<ShaderFile> geometryShaders_;
    };

    Shader();
    Shader(unsigned int rendererId);
    ~Shader();

    static Builder create(const std::string& glslVersion) { return Builder(glslVersion); }

    void bind() const;
    void unbind() const;
    void destroy() const;
    void setUniform1i(const std::string& name, int v0);
    void setUniform1f(const std::string& name, float v0);
    void setUniform2f(const std::string& name, float v0, float v1);
    void setUniform3f(const std::string& name, float v0, float v1, float v2);
    void setUniform4f(const std::string& name, float v0, float v1, float v3, float v4);
    void setUniformMatrix4fv(const std::string& name, glm::mat4& matrix);
    void setUniformMatrix3fv(const std::string& name, glm::mat3& matrix);
    inline unsigned int getRendererId();

private:

    unsigned int getUniformLocation(const std::string& name);

    unsigned int rendererId_;
    std::unordered_map<std::string, unsigned int> uniformLocationCache_;

};

