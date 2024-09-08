#pragma once

#include "Turtle/ResourceHandling/EngineSettings.h"
#include "Turtle/Window/Window.h"
#include "Turtle/Rendering/UserInterface.h"

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
		static UserInterface* UserInterface;

	private:
		static constexpr char* EngineSettingsJsonPath = "EngineSettings.json";
	};
}