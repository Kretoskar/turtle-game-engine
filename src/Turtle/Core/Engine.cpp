#include "Turtle/Core/Engine.h"
#include "Turtle/Core/Logger.h"
#include "Turtle/Core/EventSystem.h"
#include <iostream>

Turtle::Engine* Turtle::Engine::EngineInstance = nullptr;
Turtle::EngineSettings* Turtle::Engine::EngineSettings = nullptr;
Turtle::Window* Turtle::Engine::MainWindow = nullptr;

bool Turtle::Engine::Init()
{
	if (Turtle::Engine::EngineInstance)
	{
		TURTLE_LOG_ERROR("Engine already running")

		return false;
	}

	Turtle::Engine::EngineInstance = new Turtle::Engine();
	Turtle::Engine::EngineSettings = new Turtle::EngineSettings(EngineSettingsJsonPath);

	Turtle::Dispatcher::Init();
	Turtle::Engine::MainWindow = new Turtle::Window();
	

	if (!Turtle::Engine::MainWindow->Init())
	{
		return false;
	}

	return true;
}

void Turtle::Engine::Loop()
{
	Turtle::Engine::MainWindow->Loop();
}

void Turtle::Engine::ShutDown()
{
	delete Turtle::Engine::MainWindow;
	delete Turtle::Engine::EngineInstance;
	delete Turtle::Engine::EngineSettings;

	Turtle::Dispatcher::Cleanup();
}