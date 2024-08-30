#include "Turtle/Core/Engine.h"
#include "Turtle/Core/Logger.h"

Turtle::Engine* Turtle::Engine::EngineInstance = nullptr;

bool Turtle::Engine::Init()
{
	if (Turtle::Engine::EngineInstance)
	{
		TURTLE_LOG_ERROR("Engine already running")

		return false;
	}

	Turtle::Engine::EngineInstance = new Turtle::Engine();
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
}
