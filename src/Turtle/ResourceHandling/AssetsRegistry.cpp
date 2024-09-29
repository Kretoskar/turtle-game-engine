#include "Turtle/ResourceHandling/AssetsRegistry.h"
#include "Turtle/Rendering/Shader.h"
#include "Turtle/Rendering/Vertex.h"
#include "Turtle/Rendering/Material.h"
#include "Turtle/Rendering/Mesh.h"
#include "Turtle/Rendering/Texture.h"

#include <glad/glad.h>

void Turtle::AssetsRegistry::Init()
{
    std::vector<Vertex> vertices =
    {
        Vertex{glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
        Vertex{glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
        Vertex{glm::vec3(1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}
    };

    std::vector<unsigned> indices =
    {
        0, 1, 2,
        0, 2, 3
    };

    MeshDiffuseMap = std::make_shared<Texture>("base.png", GL_TEXTURE0, GL_RGB);
    MeshDiffuseMap->Bind();
    
    PbrShader = std::make_shared<Shader>("Shaders/pbr.frag", "Shaders/pbr.vert");
    PbrShader->Bind();
    PbrShader->AssignDiffuseMap(*MeshDiffuseMap.get());
  
    MeshMaterial = std::make_shared<Material>(
        MeshDiffuseMap.get(),
        nullptr,
        *PbrShader);

    Mesh = std::make_shared<Turtle::Mesh>(
        vertices,
        indices,
        MeshMaterial.get());

    DebugShader= std::make_shared<Shader>("Shaders/debug.frag", "Shaders/debug.vert");
    DebugShader->Bind();

    DebugMaterial = std::make_shared <Material>(nullptr, nullptr, *DebugShader);
    DebugMaterial->Bind();
}

void Turtle::AssetsRegistry::Cleanup()
{
	if (PbrShader)
	{
		PbrShader->Delete();
	}
}
