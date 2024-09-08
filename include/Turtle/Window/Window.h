#pragma once

#include <cstdint>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Turtle/Core/TurtleString.h"

namespace Turtle
{
	class Window
	{
	public:
		~Window();

		bool Init();
		void Update();
		void Shutdown();

		GLFWwindow* GetGlfwWindow() const { return _glfwWindow; }
		bool GetShouldClose() const { return _glfwWindow ? glfwWindowShouldClose(_glfwWindow) : false; }

		bool GetIsValid() const {}

	private:
		void BindWindowEvents();

		void HandleWindowMoveEvents(int xpos, int ypos);
		void HandleWindowMinimizedEvents(int minimized);
		void HandleWindowMaximizedEvents(int maximized);
		void HandleWindowCloseEvents();

		void HandleKeyEvents(int key, int scancode, int action, int mods);
		void HandleMouseButtonEvents(int button, int action, int mods);
		void HandleMousePositionEvents(double xpos, double ypos);
		void HandleMouseEnterLeaveEvents(int enter);

		GLFWwindow* _glfwWindow = nullptr;
		bool _isValid = false;

		uint32_t _width, _height;
		TurtleString _name;
	}; 
}