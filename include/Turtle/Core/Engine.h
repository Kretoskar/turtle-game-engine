#pragma once

namespace Turtle
{
	class EngineSettings;
	class Window;
	class UserInterface;
	class Renderer;
	class Camera;
	class DebugRenderer;

	class Engine
	{
	public:
		static bool Init();
		static void Loop();
		static void ShutDown();

		static Engine* EngineInstance;
		static EngineSettings* EngineSettings;
		static Window* MainWindow;
		static UserInterface* UserInterface;
		static Renderer* Renderer;
		static Camera* Camera;
		static DebugRenderer* DebugRenderer;

	private:
		static constexpr char* EngineSettingsJsonPath = "EngineSettings.json";
	};
}