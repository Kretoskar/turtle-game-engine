#include <iostream>

#include "Turtle/ECS/ECS.h"
#include "Turtle/ECS/Components/TransformComponent.h"
#include "Turtle/ECS/Systems/TEST_TransformSystem.h"
#include "Turtle/Core/Engine.h"

using namespace Turtle;

int main()
{
	Turtle::ECS ecs;
	
	// First register components
	ecs.RegisterComponent<Turtle::TransformComponent>();

	// Then register component in system
	TransformSystem sys;
	ecs.RegisterSystem(&sys);
	ecs.RegisterComponentInSystem<TransformComponent>(sys);

	// Then add comp to entity
	Entity e = ecs.CreateEntity();
	ecs.AddComponent<TransformComponent>(e);
	TransformComponent& t = ecs.GetComponent<TransformComponent>(e);

	for (int i = 0; i < 100; i++)
	{
		sys.Update(&ecs);
	}

	sys.Finish(&ecs);

	if (Turtle::Engine::Init())
	{
		Turtle::Engine::Loop();
		Turtle::Engine::ShutDown();
	}
}