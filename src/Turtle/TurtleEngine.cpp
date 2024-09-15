#include <iostream>

#include "Turtle/ECS/ECS.h"
#include "Turtle/ECS/Components/TransformComponent.h"
#include "Turtle/ECS/Systems/TEST_TransformSystem.h"
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