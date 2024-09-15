#pragma once

#include "Turtle/ECS/System.h"

namespace Turtle
{
	class RenderingSystem : public System
	{
	public:
		void Render();
	};
}