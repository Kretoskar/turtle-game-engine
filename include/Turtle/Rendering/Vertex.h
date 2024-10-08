#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace Turtle
{
    struct Vertex
    {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec3 Color;
        glm::vec2 TexUV;
    };
}