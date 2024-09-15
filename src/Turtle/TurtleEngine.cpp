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
	ecs.RegisterComponent<TransformComponent>();
	ecs.RegisterComponent<TestCompA>();

	// Then register component in system
	TransformSystem sys;
	ecs.RegisterSystem(&sys);
	ecs.RegisterComponentInSystem<TransformComponent>(sys);

	TestSystemA sysA;
	ecs.RegisterSystem(&sysA);
	ecs.RegisterComponentInSystem<TransformComponent>(sysA);
	ecs.RegisterComponentInSystem<TestCompA>(sysA);

	// Then add comp to entity
	Entity e = ecs.CreateEntity();
	TransformComponent& t = ecs.AddComponent<TransformComponent>(e);
	t.x = 10;

	Entity e2 = ecs.CreateEntity();
	TransformComponent& tTest = ecs.AddComponent<TransformComponent>(e2);
	tTest.x = 0;
	TestCompA& a = ecs.AddComponent<TestCompA>(e2);
	a.x = 1000;

	for (int i = 0; i < 100; i++)
	{
		sys.Update(&ecs);
		sysA.Update(&ecs);
	}

	sys.Finish(&ecs);
	sysA.Finish(&ecs);

	if (Turtle::Engine::Init())
	{
		Turtle::Engine::Loop();
		Turtle::Engine::ShutDown();
	}
}