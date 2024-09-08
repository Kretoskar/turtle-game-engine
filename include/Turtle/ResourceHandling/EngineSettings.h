#pragma once

#include <cstdint>
#include "Turtle/Core/TurtleString.h"
#include "glm/vec3.hpp"

namespace Turtle
{
	struct EngineSettings
	{
		EngineSettings(const char* jsonPath);

		struct Window
		{
			TurtleString Name;
			uint32_t Width;
			uint32_t Height;
			glm::vec3 BgColor;
		};

		const Window& WindowSetting() const { return _windowSettings; }

	private:
		Window _windowSettings;
	};
}