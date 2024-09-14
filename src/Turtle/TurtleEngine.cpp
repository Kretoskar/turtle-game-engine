#include <iostream>

#include "Turtle/Core/ECS.h"
#include "Turtle/Core/Engine.h"

using namespace Turtle;

int main()
{
	Turtle::ECS ecs;
	TransformComponent comp;
	ecs.RegisterComponent<Turtle::TransformComponent>(comp.TypeName());

	Entity e = ecs.CreateEntity();
	ecs.AddComponent<TransformComponent>(e, comp, comp.TypeName());

	TransformSystem sys;
	//TODO component type from component
	sys.RegisterComponent()

	if (Turtle::Engine::Init())
	{
		Turtle::Engine::Loop();
		Turtle::Engine::ShutDown();
	}
}