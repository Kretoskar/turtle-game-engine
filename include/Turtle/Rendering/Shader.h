#pragma once

#include <string>
#include <unordered_map>

#include "glm/glm.hpp"

namespace Turtle
{
    class Texture;

    class Shader
    {
        std::string _fragmentFilePath;
        std::string _vertexFilePath;
        std::unordered_map<std::string, int> _uniformLocationCache;

        unsigned int _id;

    public:
        Shader(std::string fragmentFilePath, std::string vertexFilePath);
        ~Shader();

        void Bind() const;

        void Delete();

        void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
        void SetUniform1f(const std::string& name, float v0);
        void SetUniform2f(const std::string& name, float v0, float v1);
        void SetUniform3f(const std::string& name, float v0, float v1, float v2);
        void SetUniform1i(const std::string& name, int v0);

        void SetUniformMat4f(const std::string& name, const glm::mat4& mat);

        void AssignDiffuseMap(Texture& texture);
        void AssignSpecularMap(Texture& texture);

        void SetModelMatrix(glm::mat4 m);
        void SetVPMatrix(glm::mat4 m);
        void SetCameraPosition(glm::vec3 pos);
        void SetLightPosition(glm::vec3 pos);
        void SetLightColor(glm::vec4 color);

    private:
        int GetUniformLocation(const std::string& name);
        unsigned int CreateShader();
        unsigned int CompileShader(unsigned int type, const std::string& source);
    };
}
