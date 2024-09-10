#pragma once

namespace Turtle
{
	class Scene;

	class App
	{
		bool Init();
		void Update();
		void Exit();

		Scene* _scene;
	};
}