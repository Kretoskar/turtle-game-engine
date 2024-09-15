#include "Turtle/Game/Scene.h"
#include "Turtle/ECS/ECS.h"
#include "Turtle/ECS/Components/TransformComponent.h"

void Turtle::Scene::Init(ECS& ecs)
{
	Entity e = ecs.CreateEntity();
	TransformComponent& t = ecs.AddComponent<TransformComponent>(e);

	Entity e2 = ecs.CreateEntity();
	TransformComponent& tTest = ecs.AddComponent<TransformComponent>(e2);
}