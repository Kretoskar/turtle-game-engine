#include <glad/glad.h>

#include "Turtle/Rendering/Mesh/Mesh.h"
#include "Turtle/Rendering/Vertex.h"
#include "Turtle/Rendering/Material.h"
#include "Turtle/Rendering/VertexBufferObject.h"
#include "Turtle/Rendering/ElementBufferObject.h"

Turtle::Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned>& indices, Material* material)
    : _vertices(vertices), _indices(indices), _material(material)
{
    _vao.Bind();

    const VertexBufferObject vbo = VertexBufferObject(vertices);
    const ElementBufferObject ebo = ElementBufferObject(indices);

    // position
    _vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
    //normals
    _vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
    // color
    _vao.LinkAttrib(vbo, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
    // UV
    _vao.LinkAttrib(vbo, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));
}

Turtle::Mesh::~Mesh()
{
    _vao.Delete();
}

void Turtle::Mesh::Draw()
{
    _material->Bind();
    _vao.Bind();

    glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
}
