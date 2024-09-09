#include <glad/glad.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include "Turtle/Rendering/Renderer.h"
#include "Turtle/Core/Engine.h"
#include "Turtle/ResourceHandling/EngineSettings.h"

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
    texture = std::make_unique<Texture>("base.png", GL_TEXTURE0, GL_RGB);
    texture->Bind();

    shader = std::make_unique<Shader>("Shaders/pbr.frag", "Shaders/pbr.vert");
    shader->Bind();
    shader->AssignDiffuseMap(*texture.get());

    
    vao = std::make_unique<VertexArrayObject>();
    vao->Bind();

    vbo = std::make_unique<VertexBufferObject>(vertices, sizeof(vertices));
    ebo = std::make_unique<ElementBufferObject>(indices, sizeof(indices));

    // position
    vao->LinkAttrib(*vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    // color
    vao->LinkAttrib(*vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    // UV
    vao->LinkAttrib(*vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    
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

    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
    projection = glm::perspective(glm::radians(45.0f), (float)1920 / 1080, 0.1f, 100.0f);
    shader->SetModelMatrix(model);
    shader->SetVPMatrix(projection * view);

    shader->Bind();
    texture->Bind();
    vao->Bind();
    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
}