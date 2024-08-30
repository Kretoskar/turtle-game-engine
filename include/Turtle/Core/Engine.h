#pragma once

#include "Turtle/ResourceHandling/EngineSettings.h"
#include "Turtle/Window/Window.h"

namespace Turtle
{
	class Engine
	{
	public:
		static bool Init();
		static void Loop();
		static void ShutDown();

		static Engine* EngineInstance;
		static EngineSettings* EngineSettings;
		static Window* MainWindow;

	private:
		static constexpr char* EngineSettingsJsonPath = "EngineSettings.json";
	};
}