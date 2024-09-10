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

		std::unique_ptr<Shader> _shader;
		std::unique_ptr<VertexBufferObject> _vbo;
		std::unique_ptr<ElementBufferObject> _ebo;
		std::unique_ptr<VertexArrayObject> _vao;
		std::unique_ptr<Texture> _texture;
	};
}