#pragma once

#include <string>
#include <unordered_map>

#include "glm/glm.hpp"
#include "Turtle/Core/TurtleString.h"

namespace Turtle
{
    class Texture;

    class Shader
    {
        TurtleString _fragmentFilePath;
        TurtleString _vertexFilePath;
        std::unordered_map<TurtleString, int, TurtleString::TurtleStringHasher> _uniformLocationCache;

        unsigned int _id;

    public:
        Shader(TurtleString fragmentFilePath, TurtleString vertexFilePath);
        ~Shader();

        void Bind() const;

        void Delete();

        void SetUniform4f(TurtleString name, float v0, float v1, float v2, float v3);
        void SetUniform1f(TurtleString name, float v0);
        void SetUniform2f(TurtleString name, float v0, float v1);
        void SetUniform3f(TurtleString name, float v0, float v1, float v2);
        void SetUniform1i(TurtleString name, int v0);

        void SetUniformMat4f(TurtleString name, const glm::mat4& mat);

        void AssignDiffuseMap(Texture& texture);
        void AssignSpecularMap(Texture& texture);

        void SetModelMatrix(glm::mat4 m);
        void SetVPMatrix(glm::mat4 m);
        void SetCameraPosition(glm::vec3 pos);
        void SetLightPosition(glm::vec3 pos);
        void SetLightColor(glm::vec4 color);

    private:
        int GetUniformLocation(TurtleString name);
        unsigned int CreateShader();
        unsigned int CompileShader(unsigned int type, const std::string& source);
    };
}
