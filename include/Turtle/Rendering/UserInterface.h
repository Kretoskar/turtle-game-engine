#pragma once

#include <GLFW/glfw3.h>

namespace Turtle
{
    class UserInterface
    {
    public:
        bool Init(GLFWwindow* window);
        void CreateFrame();
        void Render();
        void Cleanup();
    };
}