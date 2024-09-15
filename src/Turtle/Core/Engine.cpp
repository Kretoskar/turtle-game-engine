#include <iostream>

#include "Turtle/Core/Engine.h"
#include "Turtle/Core/Logger.h"
#include "Turtle/Core/EventSystem.h"

#include "Turtle/ResourceHandling/EngineSettings.h"
#include "Turtle/ResourceHandling/AssetsRegistry.h"

#include "Turtle/Window/Window.h"

#include "Turtle/Rendering/UserInterface.h"
#include "Turtle/Rendering/Renderer.h"
#include "Turtle/Rendering/Camera.h"
#include "Turtle/Rendering/DebugRenderer.h"

#include "Turtle/Game/Game.h"

Turtle::Engine* Turtle::Engine::EngineInstance = nullptr;
Turtle::EngineSettings* Turtle::Engine::EngineSettings = nullptr;
Turtle::Window* Turtle::Engine::MainWindow = nullptr;
Turtle::UserInterface* Turtle::Engine::UserInterface = nullptr;
Turtle::Renderer* Turtle::Engine::Renderer = nullptr;
Turtle::Camera* Turtle::Engine::Camera = nullptr;
Turtle::DebugRenderer* Turtle::Engine::DebugRenderer = nullptr;
Turtle::AssetsRegistry* Turtle::Engine::AssetsRegistry = nullptr;
Turtle::Game* Turtle::Engine::Game = nullptr;

bool Turtle::Engine::Init()
{
	if (Turtle::Engine::EngineInstance)
	{
		TURTLE_LOG_ERROR("Engine already running")

		return false;
	}

	EngineInstance = new Engine();
	EngineSettings = new Turtle::EngineSettings(_engineSettingsJsonPath);

	Turtle::Dispatcher::Init();
	MainWindow = new Turtle::Window();
	
	if (!MainWindow->Init())
	{
		return false;
	}

	AssetsRegistry = new Turtle::AssetsRegistry();
	AssetsRegistry->Init();

	Camera = new Turtle::Camera(MainWindow, glm::vec3(0.0f, 1.0f, 0.0f));
	Camera->Init();

	Renderer = new Turtle::Renderer();
	if (!Renderer->Init())
	{
		return false;
	}

	DebugRenderer = new Turtle::DebugRenderer();
	if (!DebugRenderer->Init())
	{
		return false;
	}

	UserInterface = new Turtle::UserInterface();
	if (!UserInterface->Init(MainWindow->GetGlfwWindow()))
	{
		return false;
	}

	Game = new Turtle::Game();
	Game->InitInEditor();

	return true;
}

void Turtle::Engine::Loop()
{
	while (!MainWindow->GetShouldClose())
	{
		

		Camera->Update();
		Renderer->Render();
		DebugRenderer->Render();

		Game->LoopInEditor();

		UserInterface->CreateFrame();
		UserInterface->Render();

		MainWindow->Update();
	}
}

void Turtle::Engine::ShutDown()
{
	delete Game;
	delete MainWindow;
	delete EngineInstance;
	delete EngineSettings;
	delete Renderer;
	delete DebugRenderer;

	UserInterface->Cleanup();
	delete UserInterface;

	AssetsRegistry->Cleanup();
	delete AssetsRegistry;

	Turtle::Dispatcher::Cleanup();
}