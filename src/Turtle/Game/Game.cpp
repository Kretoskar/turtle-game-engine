#include "Turtle/Game/Game.h"
#include "Turtle/ECS/Components/TransformComponent.h"
#include "Turtle/ECS/Systems/TEST_TransformSystem.h"

namespace Turtle 
{
	Game::Game()
	{
		// First register components
		_ecs.RegisterComponent<TransformComponent>();
		_ecs.RegisterComponent<TestCompA>();

		// Then register component in system
		_ecs.RegisterSystem(&_transformSys);
		_ecs.RegisterComponentInSystem<TransformComponent>(_transformSys);

		
		_ecs.RegisterSystem(&_testASys);
		_ecs.RegisterComponentInSystem<TransformComponent>(_testASys);
		_ecs.RegisterComponentInSystem<TestCompA>(_testASys);
	}

	void Game::InitInEditor()
	{
		_scene.Init(_ecs);

		for (int i = 0; i < 100; i++)
		{
			_transformSys.Update(&_ecs);
			_testASys.Update(&_ecs);
		}

		_transformSys.Finish(&_ecs);
		_testASys.Finish(&_ecs);
	}

	void Game::LoopInEditor()
	{

	}
}