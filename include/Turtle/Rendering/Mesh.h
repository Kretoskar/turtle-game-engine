#pragma once
#include <memory>
#include <vector>

#include "Turtle/Rendering/VertexArrayObject.h"

namespace Turtle
{
    struct Vertex;
    class Material;

    class Mesh
    {
    public:
        Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned>& indices, Material* material);
        ~Mesh();

        void Draw();

    private:
        std::vector<Vertex> _vertices;
        std::vector<unsigned> _indices;
        Material* _material;
        VertexArrayObject _vao;
    };
}