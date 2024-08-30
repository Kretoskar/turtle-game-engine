#pragma once

#include "Turtle/ResourceHandling/EngineSettings.h"

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

		private:
		static constexpr char* EngineSettingsJsonPath = "EngineSettings.json";
	};
}