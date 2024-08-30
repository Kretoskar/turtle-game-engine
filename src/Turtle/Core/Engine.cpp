#include "Turtle/Core/Engine.h"
#include "Turtle/Core/Logger.h"
#include <iostream>

Turtle::Engine* Turtle::Engine::EngineInstance = nullptr;
Turtle::EngineSettings* Turtle::Engine::EngineSettings = nullptr;

bool Turtle::Engine::Init()
{
	if (Turtle::Engine::EngineInstance)
	{
		TURTLE_LOG_ERROR("Engine already running")

		return false;
	}

	Turtle::Engine::EngineInstance = new Turtle::Engine();
	Turtle::Engine::EngineSettings = new Turtle::EngineSettings(EngineSettingsJsonPath);

	std::cout << Turtle::Engine::EngineSettings->WindowSetting().Name.Get();

	return true;
}

void Turtle::Engine::Loop()
{
	while (true)
	{

	}
}

void Turtle::Engine::ShutDown()
{
	delete Turtle::Engine::EngineInstance;
	delete Turtle::Engine::EngineSettings;
}
