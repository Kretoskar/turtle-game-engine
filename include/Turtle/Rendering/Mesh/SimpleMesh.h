#pragma once

#include "Turtle/Rendering/Mesh/Mesh.h"
#include "Turtle/Rendering/Vertex.h"

namespace Turtle
{
	class SimpleMesh : public Mesh
	{
	public:
		SimpleMesh() {};
		// TODO: std::move?
		SimpleMesh(const std::vector<Vertex>& vertices);
		virtual ~SimpleMesh() {}
	};
}