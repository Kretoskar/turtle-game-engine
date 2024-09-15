#include <glad/glad.h>
#include "Turtle/Rendering/Renderer.h"
#include "Turtle/Core/Engine.h"
#include "Turtle/ResourceHandling/EngineSettings.h"

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
}