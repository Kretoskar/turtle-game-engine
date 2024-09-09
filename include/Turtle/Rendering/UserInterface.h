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

    private:
        void CreateConsoleWidget();
        void CreateSceneWidget();
        void CreateDetailsWidget();
    };
}