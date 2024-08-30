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
		void Loop();

		GLFWwindow* GetGlfwWindow() const { return _glfwWindow; }

		bool GetIsValid() const {}

	private:
		GLFWwindow* _glfwWindow = nullptr;
		bool _isValid = false;

		uint32_t _width, _height;
		TurtleString _name;
	}; 
}