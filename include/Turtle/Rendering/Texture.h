#pragma once
#include <string>

#include <glad/glad.h>

#include "Turtle/Core/TurtleString.h"

namespace Turtle
{
    class Texture
    {
        unsigned _id;
        unsigned _type;
        unsigned _unit;
        int _width, _height, _numColCh;

    public:
        Texture(TurtleString path, unsigned unit, unsigned format, unsigned pixelType = GL_UNSIGNED_BYTE, unsigned texType = GL_TEXTURE_2D);
        void Bind();
        void Delete();
    };
}