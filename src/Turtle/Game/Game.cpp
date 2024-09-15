#include "Turtle/Game/Game.h"
#include "Turtle/ECS/Components/TransformComponent.h"
#include "Turtle/ECS/Components/NameComponent.h"

namespace Turtle 
{
	Game::Game()
	{
		// First register components
		_ecs.RegisterComponent<TransformComponent>();
		_ecs.RegisterComponent<NameComponent>();

		// Then register component in system
		/*
		_ecs.RegisterSystem(&_transformSys);
		_ecs.RegisterComponentInSystem<TransformComponent>(_transformSys);

		
		_ecs.RegisterSystem(&_testASys);
		_ecs.RegisterComponentInSystem<TransformComponent>(_testASys);
		_ecs.RegisterComponentInSystem<TestCompA>(_testASys);
		*/
	}

	void Game::InitInEditor()
	{
		_scene.Init(_ecs);
	}

	void Game::LoopInEditor()
	{

	}
}