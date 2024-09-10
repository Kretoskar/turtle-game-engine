#pragma once

#include <vector>
#include "Turtle/Core/TurtleString.h"

namespace Turtle
{
	class EntityComponent;

	class Entity
	{
		TurtleString _name;

		Entity* _parent = nullptr;
		std::vector<Entity*> _children;
		std::vector<EntityComponent*> _components;
	};
}