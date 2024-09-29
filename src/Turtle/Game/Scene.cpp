#include <string>

#include "Turtle/Game/Scene.h"
#include "Turtle/ECS/ECS.h"
#include "Turtle/ECS/Components/TransformComponent.h"
#include "Turtle/ECS/Components/MeshComponent.h"
#include "Turtle/ECS/Components/NameComponent.h"
#include "Turtle/Core/Engine.h"
#include "Turtle/ResourceHandling/AssetsRegistry.h"



void Turtle::Scene::Init(ECS& ecs)
{
	for (uint32_t i = 0; i < 10000; i++)
	{
		Entity e = ecs.CreateEntity();
		
		TransformComponent& t = ecs.AddComponent<TransformComponent>(e);
		t.x = (float)i / 10;
		t.y = (float)i / 10;
		t.z = (float)i / 10;
		
		MeshComponent& m = ecs.AddComponent<MeshComponent>(e);
		m.Mesh = Turtle::Engine::AssetsRegistry->Mesh.get();

		NameComponent& n = ecs.AddComponent<NameComponent>(e);

		char buffer[100];
		sprintf(buffer, "floor %i", i);

		n.Name = TurtleString(buffer);
	}
}