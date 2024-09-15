#include "Turtle/Game/Scene.h"
#include "Turtle/ECS/ECS.h"
#include "Turtle/ECS/Components/TransformComponent.h"

void Turtle::Scene::Init(ECS& ecs)
{
	Entity e = ecs.CreateEntity();
	TransformComponent& t = ecs.AddComponent<TransformComponent>(e);
	t.x = 10;

	Entity e2 = ecs.CreateEntity();
	TransformComponent& tTest = ecs.AddComponent<TransformComponent>(e2);
	tTest.x = 0;
	TestCompA& a = ecs.AddComponent<TestCompA>(e2);
	a.x = 1000;
}