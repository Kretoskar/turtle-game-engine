// register systems and components here 
//and entities on scene

#pragma once

#include "Turtle/ECS/ECS.h"
#include "Turtle/Game/Scene.h"

namespace Turtle
{
	class Game
	{
	public:
		Game();

		void InitInEditor();
		void LoopInEditor();

	private:
		Scene _scene;
		ECS _ecs;
	};
}