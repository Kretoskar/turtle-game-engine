#pragma once

#include "Turtle/Core/TurtleString.h"

namespace Turtle
{
	struct Component
	{
		// TODO: maybe avoid inheritance by using typeid instead?
		virtual TurtleString TypeName() const { return TurtleString::None; }
	};
}