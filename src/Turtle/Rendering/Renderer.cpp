#include <glad/glad.h>
#include "Turtle/Rendering/Renderer.h"

bool Turtle::Renderer::Init()
{
	glClearColor(0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST);

	return true;
}

void Turtle::Renderer::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}