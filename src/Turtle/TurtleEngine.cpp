#include <iostream>

#include "Turtle/Core/Engine.h"

using namespace Turtle;

int main()
{	
	if (Turtle::Engine::Init())
	{
		Turtle::Engine::Loop();
		Turtle::Engine::ShutDown();
	}
}