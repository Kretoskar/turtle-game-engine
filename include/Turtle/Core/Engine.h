#pragma once

namespace Turtle
{
	class Engine
	{
	public:
		static bool Init();
		static void Loop();
		static void ShutDown();

		static Engine* _engineInstance;
	};
}