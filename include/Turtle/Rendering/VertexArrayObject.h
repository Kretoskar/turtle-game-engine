#pragma once

namespace Turtle
{
    class VertexBufferObject;

    class VertexArrayObject
    {

    public:
        unsigned int _id;
        VertexArrayObject();

        void LinkAttrib(const VertexBufferObject& vbo, unsigned layout, int numComponents, unsigned type, int stride, void* offset);
        void Bind();
        void Delete();
    };
}