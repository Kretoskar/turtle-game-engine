#include "Turtle/Window/Window.h"
#include "Turtle/Core/Logger.h"
#include "Turtle/Core/Engine.h"
#include "Turtle/Core/EventSystem.h"
#include "Turtle/ResourceHandling/EngineSettings.h"

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

	_width = Turtle::Engine::EngineSettings->GetWindowSettings().Width;
	_height = Turtle::Engine::EngineSettings->GetWindowSettings().Height;
	_name = Turtle::Engine::EngineSettings->GetWindowSettings().Name;

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

	BindWindowEvents();

	return true;
}

void Turtle::Window::Update()
{
	glfwSwapBuffers(_glfwWindow);
	glfwPollEvents();
}

void Turtle::Window::Shutdown()
{

}

void Turtle::Window::BindWindowEvents()
{
	/* Save the pointer to the instance as user pointer */
	glfwSetWindowUserPointer(_glfwWindow, this);

	/* Use a lambda to get the pointer and call the member function */
	glfwSetWindowPosCallback(_glfwWindow, [](GLFWwindow* win, int xpos, int ypos)
	{
		const auto thisWindow = static_cast<Window*>(glfwGetWindowUserPointer(win));
		thisWindow->HandleWindowMoveEvents(xpos, ypos);
	});

	glfwSetWindowIconifyCallback(_glfwWindow, [](GLFWwindow* win, int minimized)
	{
		const auto thisWindow = static_cast<Window*>(glfwGetWindowUserPointer(win));
		thisWindow->HandleWindowMinimizedEvents(minimized);
	});

	glfwSetWindowMaximizeCallback(_glfwWindow, [](GLFWwindow* win, int maximized)
	{
		const auto thisWindow = static_cast<Window*>(glfwGetWindowUserPointer(win));
		thisWindow->HandleWindowMaximizedEvents(maximized);
	});

	glfwSetWindowCloseCallback(_glfwWindow, [](GLFWwindow* win)
	{
		const auto thisWindow = static_cast<Window*>(glfwGetWindowUserPointer(win));
		thisWindow->HandleWindowCloseEvents();
	});

	glfwSetKeyCallback(_glfwWindow, [](GLFWwindow* win, int key, int scancode, int action, int mods)
	{
		const auto thisWindow = static_cast<Window*>(glfwGetWindowUserPointer(win));
		thisWindow->HandleKeyEvents(key, scancode, action, mods);
	});

	glfwSetMouseButtonCallback(_glfwWindow, [](GLFWwindow* win, int button, int action, int mods)
	{
		const auto thisWindow = static_cast<Window*>(glfwGetWindowUserPointer(win));
		thisWindow->HandleMouseButtonEvents(button, action, mods);
	});

	glfwSetCursorPosCallback(_glfwWindow, [](GLFWwindow* win, double xpos, double ypos)
	{
		const auto thisWindow = static_cast<Window*>(glfwGetWindowUserPointer(win));
		thisWindow->HandleMousePositionEvents(xpos, ypos);
	});

	glfwSetCursorEnterCallback(_glfwWindow, [](GLFWwindow* win, int enter)
	{
		const auto thisWindow = static_cast<Window*>(glfwGetWindowUserPointer(win));
		thisWindow->HandleMouseEnterLeaveEvents(enter);
	});
}

void Turtle::Window::HandleWindowMoveEvents(int xpos, int ypos)
{
	TURTLE_LOG_MESSAGE("Window moved: x: %i y: %i", xpos, ypos)
}

void Turtle::Window::HandleWindowMinimizedEvents(int minimized)
{
	if (minimized)
	{
		TURTLE_LOG_MESSAGE("Window has been minimized")
	}
	else
	{
		TURTLE_LOG_MESSAGE("Window has been restored")
	}
}

void Turtle::Window::HandleWindowMaximizedEvents(int maximized)
{
	if (maximized)
	{
		TURTLE_LOG_MESSAGE("Window has been maximized")
	}
	else
	{
		TURTLE_LOG_MESSAGE("Window has been restored")
	}
}

void Turtle::Window::HandleWindowCloseEvents()
{
	TURTLE_LOG_MESSAGE("Window has been closed")
}

void Turtle::Window::HandleKeyEvents(int key, int scancode, int action, int mods)
{
	std::string actionName;

	switch (action)
	{
	case GLFW_PRESS:
		actionName = "pressed";
		break;
	case GLFW_RELEASE:
		actionName = "released";
		break;
	case GLFW_REPEAT:
		actionName = "repeated";
		break;
	default:
		actionName = "invalid";
		break;
	}

	TURTLE_POST_EVENT(KeyboardEvent::Type(key, action, mods), nullptr)

	const char* keyName = glfwGetKeyName(key, 0);
	TURTLE_LOG_MESSAGE("key %s (key %i, scancode %i) %s", keyName, key, scancode, actionName.c_str())
}

void Turtle::Window::HandleMouseButtonEvents(int button, int action, int mods)
{
	std::string actionName;

	switch (action)
	{
	case GLFW_PRESS:
		actionName = "pressed";
		break;
	case GLFW_RELEASE:
		actionName = "released";
		break;
	case GLFW_REPEAT:
		actionName = "repeated";
		break;
	default:
		actionName = "invalid";
		break;
	}

	std::string mouseButtonName;
	switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
		mouseButtonName = "left";
		break;
	case GLFW_MOUSE_BUTTON_MIDDLE:
		mouseButtonName = "middle";
		break;
	case GLFW_MOUSE_BUTTON_RIGHT:
		mouseButtonName = "right";
		break;
	default:
		mouseButtonName = "other";
		break;
	}

	TURTLE_POST_EVENT(MouseButtonEvent::Type(button, action, mods), nullptr)
	TURTLE_LOG_MESSAGE("%s mouse button (%i) %s with mod %i", mouseButtonName.c_str(), button, actionName.c_str(), mods)
}

void Turtle::Window::HandleMousePositionEvents(double xpos, double ypos)
{
	MousePositionEvent::MousePositionEventPayload payload = { static_cast<int>(xpos), static_cast<int>(ypos) };
	TURTLE_POST_EVENT(MousePositionEvent::Type(), &payload)
}

void Turtle::Window::HandleMouseEnterLeaveEvents(int enter)
{
	if (enter)
	{
		TURTLE_LOG_MESSAGE("Mouse entered window")
	}
	else
	{
		TURTLE_LOG_MESSAGE("Mouse left window")
	}
}
