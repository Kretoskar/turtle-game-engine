#pragma once
#include "Turtle/Rendering/Shader.h"
#include "Turtle/Rendering/VertexBufferObject.h"
#include "Turtle/Rendering/ElementBufferObject.h"
#include "Turtle/Rendering/VertexArrayObject.h"
#include "Turtle/Rendering/Texture.h"

#include <memory>

namespace Turtle
{
	class Renderer
	{
	public:
		bool Init();
		void Render();

		std::unique_ptr<Shader> shader;
		std::unique_ptr<VertexBufferObject> vbo;
		std::unique_ptr<ElementBufferObject> ebo;
		std::unique_ptr<VertexArrayObject> vao;
		std::unique_ptr<Texture> texture;
	};
}