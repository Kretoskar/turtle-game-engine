#include <glad/glad.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include "Turtle/Rendering/Renderer.h"
#include "Turtle/Core/Engine.h"
#include "Turtle/ResourceHandling/EngineSettings.h"
#include "Turtle/Rendering/Camera.h"

// Vertices coordinates
float vertices[] =
{
    -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
    -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
     0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
     0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
     0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
};

// Indices for vertices order
unsigned indices[] =
{
    0, 1, 2,
    0, 2, 3,
    0, 1, 4,
    1, 2, 4,
    2, 3, 4,
    3, 0, 4
};

bool Turtle::Renderer::Init()
{
    _texture = std::make_unique<Texture>("base.png", GL_TEXTURE0, GL_RGB);
    _texture->Bind();

    _shader = std::make_unique<Shader>("Shaders/pbr.frag", "Shaders/pbr.vert");
    _shader->Bind();
    _shader->AssignDiffuseMap(*_texture.get());

    
    _vao = std::make_unique<VertexArrayObject>();
    _vao->Bind();

    _vbo = std::make_unique<VertexBufferObject>(vertices, sizeof(vertices));
    _ebo = std::make_unique<ElementBufferObject>(indices, sizeof(indices));

    // position
    _vao->LinkAttrib(*_vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    // color
    _vao->LinkAttrib(*_vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    // UV
    _vao->LinkAttrib(*_vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	glClearColor(
		Turtle::Engine::EngineSettings->WindowSetting().BgColor.r / 255,
		Turtle::Engine::EngineSettings->WindowSetting().BgColor.g / 255,
		Turtle::Engine::EngineSettings->WindowSetting().BgColor.b / 255,
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

    _shader->SetModelMatrix(model);
    _shader->SetVPMatrix(Engine::Camera->GetVPMatrix());

    _shader->Bind();
    _texture->Bind();
    _vao->Bind();
    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
}