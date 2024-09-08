#pragma once
#include <vector>

namespace Turtle
{
    class ElementBufferObject
    {
    public:
        unsigned int _id;

        ElementBufferObject(unsigned int* indices, long long size);
        ElementBufferObject(const std::vector<unsigned>& indices);
        void Init(const std::vector<unsigned>& indices);
        void Init(unsigned int* indices, long long size);

        void Bind() const;
        void Delete();
    };
}