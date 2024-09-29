#include "Turtle/Rendering/Mesh/SimpleMesh.h"
#include "Turtle/Rendering/Material.h"
#include "Turtle/Core/Engine.h"
#include "Turtle/ResourceHandling/AssetsRegistry.h"


Turtle::SimpleMesh::SimpleMesh(const std::vector<Vertex>& vertices)
{
	std::vector<unsigned> indices;
	indices.reserve(vertices.size());

	for (size_t i = 0; i < vertices.size(); ++i)
	{
		indices.push_back(i);
	}


	Init(vertices, indices, Engine::AssetsRegistry->DebugMaterial.get());
}
