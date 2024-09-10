#include "Turtle/Rendering/Shader.h"
#include "Turtle/ResourceHandling/File.h"
#include <sstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include "Turtle/Core/Logger.h"
#include "Turtle/Rendering/Texture.h"

Turtle::Shader::Shader(TurtleString fragmentFilePath, TurtleString vertexFilePath)
    : _fragmentFilePath(fragmentFilePath), _vertexFilePath(vertexFilePath)
{
    _id = CreateShader();
}

Turtle::Shader::~Shader()
{
    glDeleteProgram(_id);
}

void Turtle::Shader::Bind() const
{
    glUseProgram(_id);
}

void Turtle::Shader::Delete()
{
    glDeleteProgram(_id);
}

void Turtle::Shader::SetUniform4f(TurtleString name, float v0, float v1, float v2, float v3)
{
    Bind();
    glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void Turtle::Shader::SetUniform1f(TurtleString name, float v0)
{
    Bind();
    glUniform1f(GetUniformLocation(name), v0);
}

void Turtle::Shader::SetUniform2f(TurtleString name, float v0, float v1)
{
    Bind();
    glUniform2f(GetUniformLocation(name), v0, v1);
}

void Turtle::Shader::SetUniform3f(TurtleString name, float v0, float v1, float v2)
{
    Bind();
    glUniform3f(GetUniformLocation(name), v0, v1, v2);
}

void Turtle::Shader::SetUniform1i(TurtleString name, int v0)
{
    Bind();
    glUniform1i(GetUniformLocation(name), v0);
}

void Turtle::Shader::SetUniformMat4f(TurtleString name, const glm::mat4& mat)
{
    Bind();
    // pass with no transpose bcs both glm and opengl use column major matrices
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}

void Turtle::Shader::AssignDiffuseMap(Texture& texture)
{
    Bind();
    texture.Bind();
    SetUniform1i("diffuseMap", 0);
}

void Turtle::Shader::AssignSpecularMap(Texture& texture)
{
    Bind();
    texture.Bind();
    SetUniform1i("specularMap", 1);
}

void Turtle::Shader::SetModelMatrix(glm::mat4 m)
{
    Bind();
    SetUniformMat4f("model", m);
}

void Turtle::Shader::SetVPMatrix(glm::mat4 m)
{
    Bind();
    SetUniformMat4f("viewProj", m);
}

void Turtle::Shader::SetCameraPosition(glm::vec3 pos)
{
    Bind();
    SetUniform3f("cameraPos", pos.x, pos.y, pos.z);
}

void Turtle::Shader::SetLightPosition(glm::vec3 pos)
{
    Bind();
    SetUniform3f("lightPos", pos.x, pos.y, pos.z);
}

void Turtle::Shader::SetLightColor(glm::vec4 color)
{
    Bind();
    SetUniform4f("lightColor", color.x, color.y, color.z, color.w);
}

int Turtle::Shader::GetUniformLocation(TurtleString name)
{
    Bind();
    if (_uniformLocationCache.find(name) != _uniformLocationCache.end())
    {
        return _uniformLocationCache[name];
    }

    const int location = glGetUniformLocation(_id, name.Get());
    _uniformLocationCache[name] = location;

    if (location < 0)
    {
        TURTLE_LOG_WARNING("Trying to retrieve invalid uniform location of name %s", name)
    }

    return 1;
}

unsigned Turtle::Shader::CreateShader()
{
    Turtle::File vertexShaderFile (_vertexFilePath.Get());

    if (!vertexShaderFile.IsValid())
    {
        TURTLE_LOG_ERROR("Failed to create vertex shader")
        return 0;
    }

    Turtle::File fragmentShaderFile(_fragmentFilePath.Get());

    if (!fragmentShaderFile.IsValid())
    {
        TURTLE_LOG_ERROR("Failed to create fragment shader")
        return 0;
    }

    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, *vertexShaderFile.GetFileContents());
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, *fragmentShaderFile.GetFileContents());

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

unsigned Turtle::Shader::CompileShader(unsigned type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* scr = source.c_str();
    glShaderSource(id, 1, &scr, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = static_cast<char*>(alloca(length * sizeof(char)));
        glGetShaderInfoLog(id, length, &length, message);

        TURTLE_LOG_ERROR(message)
            glDeleteShader(id);

        return 0;
    }

    return id;
}