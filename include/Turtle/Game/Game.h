// register systems and components here 
//and entities on scene

#pragma once

#include "Turtle/ECS/ECS.h"
#include "Turtle/Game/Scene.h"
#include "Turtle/ECS/Systems/RenderingSystem.h"

namespace Turtle
{
	class Game
	{
	public:
		Game();

		void InitInEditor();
		void LoopInEditor();

	private:
		void RegisterComponents();
		void RegisterSystems();

		Scene _scene;
		ECS _ecs;

		RenderingSystem _renderingSystem;
	};
}