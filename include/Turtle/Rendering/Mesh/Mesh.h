#pragma once
#include <memory>
#include <vector>

#include "Turtle/Rendering/Vertex.h"
#include "Turtle/Rendering/VertexArrayObject.h"

namespace Turtle
{
    struct Vertex;
    class Material;

    class Mesh
    {
    public:
        Mesh() {}
        Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned>& indices, Material* material);
        virtual ~Mesh();

        void Draw();
        Material* GetMaterial() const { return _material; }

    private:
        std::vector<Vertex> _vertices;
        std::vector<unsigned> _indices;
        Material* _material;
        VertexArrayObject _vao;
    };
}