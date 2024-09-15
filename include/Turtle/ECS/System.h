#pragma once

#include <set>

#include "Turtle/ECS/ECSTypes.h"

namespace Turtle
{
	class System
	{
	public:

		Signature _sig{};
		std::set<Entity> _entities{};
	};
}