#pragma once

#include "Turtle/Rendering/Mesh/Mesh.h"
#include "Turtle/Rendering/Vertex.h"

namespace Turtle
{
	class SimpleMesh : public Mesh
	{
		SimpleMesh() = delete;
		SimpleMesh(const std::vector<Vertex>& vertices);
		virtual ~SimpleMesh() {}
	};
}