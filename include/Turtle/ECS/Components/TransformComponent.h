#pragma once

#include "Turtle/Core/TurtleString.h"

namespace Turtle
{
	struct TransformComponent : public Component
	{
		float x{}, y{}, z{};
		virtual TurtleString TypeName() const { return TurtleString("Transform"); }
	};
}