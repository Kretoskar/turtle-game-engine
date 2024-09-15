#include <iostream>

#include "Turtle/ECS/ECS.h"
#include "Turtle/Core/Engine.h"

using namespace Turtle;

int main()
{
	Turtle::ECS ecs;
	
	// First register components
	TransformComponent comp;
	ecs.RegisterComponent<Turtle::TransformComponent>(comp.TypeName());

	// Then register component in system
	TransformSystem sys;
	ecs.RegisterSystem(&sys);
	ecs.RegisterComponentInSystem(sys, comp);

	// Then add comp to entity
	Entity e = ecs.CreateEntity();
	ecs.AddComponent<TransformComponent>(e, comp, comp.TypeName());

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