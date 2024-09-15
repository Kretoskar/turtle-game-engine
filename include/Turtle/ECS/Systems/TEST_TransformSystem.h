#pragma once

#include "Turtle/ECS/ECSTypes.h"
#include "Turtle/ECS/Components/TransformComponent.h"
#include "Turtle/ECS/ECS.h"

namespace Turtle
{
	class TransformSystem : public System
	{
	public:
		void Update(ECS* ecs)
		{
			for (Entity e : _entities)
			{
				TransformComponent& comp = ecs->GetComponent<TransformComponent>(e);
				comp.x += 1;
			}
		}

		void Finish(ECS* ecs)
		{
			for (Entity e : _entities)
			{
				TransformComponent comp = ecs->GetComponent<TransformComponent>(e);
				TURTLE_LOG_MESSAGE("X: %f", comp.x)
			}
		}
	};

	class TestSystemA : public System
	{
	public:
		void Update(ECS* ecs)
		{
			for (Entity e : _entities)
			{
				TransformComponent& comp = ecs->GetComponent<TransformComponent>(e);
				TestCompA& compA = ecs->GetComponent<TestCompA>(e);
				comp.x += 1;
				compA.x -= 1;
			}
		}

		void Finish(ECS* ecs)
		{
			for (Entity e : _entities)
			{
				TransformComponent comp = ecs->GetComponent<TransformComponent>(e);
				TestCompA& compA = ecs->GetComponent<TestCompA>(e);
				TURTLE_LOG_MESSAGE("X: %f Ax: %f", comp.x, compA.x)
			}
		}
	};
}