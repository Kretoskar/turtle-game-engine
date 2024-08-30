#include "Turtle/Window/Window.h"
#include "Turtle/Core/Logger.h"
#include "Turtle/Core/Engine.h"

Turtle::Window::~Window()
{
	glfwDestroyWindow(_glfwWindow);
	glfwTerminate();
}

bool Turtle::Window::Init()
{
	if (!glfwInit())
	{
		TURTLE_LOG_ERROR("Failed to initialize window")
		return false;
	}

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_width = Turtle::Engine::EngineSettings->WindowSetting().Width;
	_height = Turtle::Engine::EngineSettings->WindowSetting().Height;
	_name = Turtle::Engine::EngineSettings->WindowSetting().Name;

	_glfwWindow = glfwCreateWindow(
		_width,
		_height,
		_name.Get(),
		nullptr,
		nullptr);

	if (!_glfwWindow)
	{
		TURTLE_LOG_ERROR("Failed to initialize window")
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(_glfwWindow);
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		TURTLE_LOG_ERROR("Failed to initialize GLAD")
		return false;
	}

	glViewport(0, 0, _width, _height);
	glClearColor(0.15f, 0.5f, 1.0f, 1.0f);

	// force VSYNC
	glfwSwapInterval(1);

	return true;
}

void Turtle::Window::Loop()
{
	while (!glfwWindowShouldClose(_glfwWindow))
	{
		glfwSwapBuffers(_glfwWindow);
		glfwPollEvents();
	}
}