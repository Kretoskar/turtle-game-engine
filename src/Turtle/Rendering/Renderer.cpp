#include <glad/glad.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include "Turtle/Rendering/Renderer.h"
#include "Turtle/Core/Engine.h"
#include "Turtle/ResourceHandling/EngineSettings.h"
#include "Turtle/Rendering/Camera.h"
#include "Turtle/Rendering/Vertex.h"
#include "Turtle/ResourceHandling/AssetsRegistry.h"

using namespace Turtle;

bool Turtle::Renderer::Init()
{
	glClearColor
	(
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

	Turtle::Engine::AssetsRegistry->PbrShader->SetModelMatrix(meshModelMat);
	Turtle::Engine::AssetsRegistry->PbrShader->SetVPMatrix(Engine::Camera->GetVPMatrix());
	Turtle::Engine::AssetsRegistry->Mesh->Draw();
}