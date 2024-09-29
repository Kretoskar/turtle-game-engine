#pragma once

#include <GLFW/glfw3.h>
#include <unordered_map>

#include "Turtle/Core/TurtleString.h"
#include "Turtle/ECS/ECSTypes.h"

namespace Turtle
{
    class UserInterface
    {
    public:
        bool Init(GLFWwindow* window);
        void CreateFrame();
        void Render();
        void Cleanup();

        void UpdateEntityMap(std::unordered_map<Entity, TurtleString> entityMap);

    private:
        void CreateConsoleWidget();
        void CreateSceneWidget();
        void CreateDetailsWidget();
        void CreateToolbarWidget();

        std::unordered_map<Entity, TurtleString> _entityMap;
    };
}