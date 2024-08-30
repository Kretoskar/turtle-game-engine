#pragma once

#include <cstdint>
#include "Turtle/Core/TurtleString.h"

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
		};

		const Window& WindowSetting() const { return _windowSettings; }

	private:
		Window _windowSettings;
	};
}