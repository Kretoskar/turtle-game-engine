#pragma once

#include <vector>

#include "Vertex.h"

namespace Turtle
{
    class VertexBufferObject
    {
    public:
        unsigned int _id;

        VertexBufferObject(float* vertices, long long size);
        VertexBufferObject(const std::vector<Vertex>& vertices);
        void Init(float* vertices, long long size);
        void Init(const std::vector<Vertex>& vertices);

        void Bind() const;
        void Delete();
    };
}