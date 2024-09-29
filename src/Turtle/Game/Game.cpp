#include "Turtle/Game/Game.h"

#include "Turtle/ECS/Components/TransformComponent.h"
#include "Turtle/ECS/Components/NameComponent.h"
#include "Turtle/ECS/Components/MeshComponent.h"

#include "Turtle/ECS/Systems/RenderingSystem.h"

namespace Turtle 
{
	Game::Game()
	{
		RegisterComponents();
		RegisterSystems();
	}

	void Game::InitInEditor()
	{
		_scene.Init(_ecs);
	}

	void Game::LoopInEditor()
	{
		_renderingSystem.Render();
		_uiSystem.Update();
	}

	void Turtle::Game::RegisterComponents()
	{
		_ecs.RegisterComponent<TransformComponent>();
		_ecs.RegisterComponent<NameComponent>();
		_ecs.RegisterComponent<MeshComponent>();
	}

	void Turtle::Game::RegisterSystems()
	{
		_ecs.RegisterSystem(&_renderingSystem);
		_ecs.RegisterComponentInSystem<TransformComponent>(_renderingSystem);
		_ecs.RegisterComponentInSystem<MeshComponent>(_renderingSystem);

		_ecs.RegisterSystem(&_uiSystem);
		_ecs.RegisterComponentInSystem<NameComponent>(_uiSystem);
	}
}