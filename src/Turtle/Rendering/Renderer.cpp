#include <glad/glad.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include "Turtle/Rendering/Renderer.h"
#include "Turtle/Core/Engine.h"
#include "Turtle/ResourceHandling/EngineSettings.h"
#include "Turtle/Rendering/Camera.h"
#include "Turtle/Rendering/Vertex.h"

using namespace Turtle;

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

bool Turtle::Renderer::Init()
{
    _texture = std::make_unique<Texture>("base.png", GL_TEXTURE0, GL_RGB);
    _texture->Bind();

    _shader = std::make_unique<Shader>("Shaders/pbr.frag", "Shaders/pbr.vert");
    _shader->Bind();
    _shader->AssignDiffuseMap(*_texture.get());

    _material = std::make_unique<Material>(_texture.get(), nullptr, *_shader.get());

    _mesh = std::make_unique<Mesh>(vertices, indices, _material.get());

	glClearColor(
		Turtle::Engine::EngineSettings->GetWindowSettings().BgColor.r / 255,
		Turtle::Engine::EngineSettings->GetWindowSettings().BgColor.g / 255,
		Turtle::Engine::EngineSettings->GetWindowSettings().BgColor.b / 255,
		0
	);

	glEnable(GL_DEPTH_TEST);

	return true;
}

void Turtle::Renderer::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    static float rot = 0;
    rot += 2;

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));

    
    glm::mat4 meshModelMat = glm::mat4(1.0f);
    meshModelMat = translate(meshModelMat, glm::vec3(0.0f, 0.1f, 0.0f));
    _shader->SetModelMatrix(meshModelMat);
    _shader->SetVPMatrix(Engine::Camera->GetVPMatrix());
    _mesh->Draw();

    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
}