#include "Turtle/Core/Engine.h"
#include "Turtle/Core/Logger.h"
#include "Turtle/Core/EventSystem.h"
#include <iostream>

#include "Turtle/ResourceHandling/EngineSettings.h"
#include "Turtle/Window/Window.h"
#include "Turtle/Rendering/UserInterface.h"
#include "Turtle/Rendering/Renderer.h"

Turtle::Engine* Turtle::Engine::EngineInstance = nullptr;
Turtle::EngineSettings* Turtle::Engine::EngineSettings = nullptr;
Turtle::Window* Turtle::Engine::MainWindow = nullptr;
Turtle::UserInterface* Turtle::Engine::UserInterface = nullptr;
Turtle::Renderer* Turtle::Engine::Renderer = nullptr;

bool Turtle::Engine::Init()
{
	if (Turtle::Engine::EngineInstance)
	{
		TURTLE_LOG_ERROR("Engine already running")

		return false;
	}

	EngineInstance = new Engine();
	EngineSettings = new Turtle::EngineSettings(EngineSettingsJsonPath);

	Turtle::Dispatcher::Init();
	MainWindow = new Turtle::Window();
	
	if (!MainWindow->Init())
	{
		return false;
	}

	Renderer = new Turtle::Renderer();
	if (!Renderer->Init())
	{
		return false;
	}

	UserInterface = new Turtle::UserInterface();
	if (!UserInterface->Init(MainWindow->GetGlfwWindow()))
	{
		return false;
	}

	return true;
}

void Turtle::Engine::Loop()
{
	while (!MainWindow->GetShouldClose())
	{
		Renderer->Render();

		UserInterface->CreateFrame();
		UserInterface->Render();

		MainWindow->Update();
	}
}

void Turtle::Engine::ShutDown()
{
	delete MainWindow;
	delete EngineInstance;
	delete EngineSettings;
	delete Renderer;

	UserInterface->Cleanup();
	delete UserInterface;

	Turtle::Dispatcher::Cleanup();
}