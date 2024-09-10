#pragma once
#include "Turtle/Rendering/Shader.h"
#include "Turtle/Rendering/VertexBufferObject.h"
#include "Turtle/Rendering/ElementBufferObject.h"
#include "Turtle/Rendering/VertexArrayObject.h"
#include "Turtle/Rendering/Texture.h"
#include "Turtle/Rendering/Material.h"
#include "Turtle/Rendering/Mesh.h"

#include <memory>

namespace Turtle
{
	class Renderer
	{
	public:
		bool Init();
		void Render();

		std::unique_ptr<Shader> _shader;
		std::unique_ptr<Texture> _texture;
		std::unique_ptr<Material> _material;
		std::unique_ptr<Mesh> _mesh;
	};
}