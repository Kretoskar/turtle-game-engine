#include "Turtle/Core/Engine.h"
#include "Turtle/Core/Logger.h"

Turtle::Engine* Turtle::Engine::_engineInstance = nullptr;

bool Turtle::Engine::Init()
{
	if (Turtle::Engine::_engineInstance)
	{
		TURTLE_LOG_ERROR("Engine already running")

		return false;
	}

	Turtle::Engine::_engineInstance = new Turtle::Engine();
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
	delete Turtle::Engine::_engineInstance;
}
