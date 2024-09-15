#pragma once

namespace Turtle
{
	class EngineSettings;
	class Window;
	class UserInterface;
	class Renderer;
	class Camera;
	class DebugRenderer;
	class AssetsRegistry;
	class Game;

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
		static AssetsRegistry* AssetsRegistry;
		static Game* Game;

	private:
		static constexpr char* _engineSettingsJsonPath = "EngineSettings.json";
	};
}