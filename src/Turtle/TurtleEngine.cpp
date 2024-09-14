#include <iostream>

#include "Turtle/Core/ECS.h"
#include "Turtle/Core/Engine.h"

int main()
{
	if (Turtle::Engine::Init())
	{
		Turtle::Engine::Loop();
		Turtle::Engine::ShutDown();
	}
}