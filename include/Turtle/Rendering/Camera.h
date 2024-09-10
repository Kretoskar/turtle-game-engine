#pragma once
#include "Turtle/Core/EventSystem.h"
#include "glm/glm.hpp"

namespace Turtle
{
    class Window;
    class Shader;

    class Camera
    {
        glm::vec3 _position;
        glm::vec3 _orientation = glm::vec3(-0.5f, -0.5f, -0.5f);
        glm::vec3 _up = glm::vec3(0.0f, 1.0f, 0.0f);

        glm::mat4 _view = glm::mat4(1.0f);
        glm::mat4 _projection = glm::mat4(1.0f);

        int _width = 1920;
        int _height = 1080;

        float _speed = 0.015f;
        float _sensitivity = 100.0f;

        float _FOVdeg = 120;
        float _nearPlane = 0.01f;
        float _farPlane = 1000;

        Window* _window;
        bool _canMove = false;
        bool _canLook = false;

        bool _movingForward = false;
        bool _movingBackward = false;
        bool _movingLeft = false;
        bool _movingRight = false;

        glm::vec3 GetVelocity() const;

    public:
        Camera(Window* inWindow, glm::vec3 position)
            : _window(inWindow), _position(position) {}
        void Init();
        void Update();

        glm::vec3 GetRightVector() const;

        void OnRightMouseButtonClick(void* event);
        void OnRightMouseButtonRelease(void* event);

        void OnForwardPressed(void* payload);
        void OnForwardReleased(void* payload);

        void OnBackwardPressed(void* payload);
        void OnBackwardReleased(void* payload);

        void OnRightPressed(void* payload);
        void OnRightReleased(void* payload);

        void OnLeftPressed(void* payload);
        void OnLeftReleased(void* payload);

        void OnMouseMoved(void* payload);

        glm::mat4 GetVPMatrix() const { return _projection * _view; }

        glm::vec3 GetPosition() const { return _position; }
    };
}