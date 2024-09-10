#include "Turtle/Rendering/Camera.h"

#define GLM_ENABLE_EXPERIMENTAL

#include "glm/glm.hpp"

#include "Turtle/Core/Logger.h"
#include "Turtle/Window/Window.h"
#include "Turtle/Rendering/Shader.h"
#include "Turtle/Core/Engine.h"
#include "Turtle/ResourceHandling/EngineSettings.h"

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

glm::vec3 Turtle::Camera::GetVelocity() const
{
    glm::vec3 retVelocity = glm::vec3(0.0f, 0.0f, 0.0f);

    if (!_canMove)
    {
        return { 0.0f, 0.0f, 0.0f };
    }

    if (_movingForward)
    {
        retVelocity += _orientation * _speed;
    }
    if (_movingBackward)
    {
        retVelocity -= _orientation * _speed;
    }
    if (_movingRight)
    {
        retVelocity += GetRightVector() * _speed;
    }
    if (_movingLeft)
    {
        retVelocity -= GetRightVector() * _speed;
    }

    return retVelocity;
}

void Turtle::Camera::Init()
{
    _width = Engine::EngineSettings->GetWindowSettings().Height;
    _height = Engine::EngineSettings->GetWindowSettings().Width;

    TURTLE_BIND_EVENT(MouseButtonEvent::Type(GLFW_MOUSE_BUTTON_RIGHT, GLFW_PRESS, 0), OnRightMouseButtonClick)
    TURTLE_BIND_EVENT(MouseButtonEvent::Type(GLFW_MOUSE_BUTTON_RIGHT, GLFW_RELEASE, 0), OnRightMouseButtonRelease)

    TURTLE_BIND_EVENT(MousePositionEvent::Type(), OnMouseMoved)

    TURTLE_BIND_EVENT(KeyboardEvent::Type(GLFW_KEY_W, GLFW_PRESS, 0), OnForwardPressed)
    TURTLE_BIND_EVENT(KeyboardEvent::Type(GLFW_KEY_W, GLFW_RELEASE, 0), OnForwardReleased)

    TURTLE_BIND_EVENT(KeyboardEvent::Type(GLFW_KEY_S, GLFW_PRESS, 0), OnBackwardPressed)
    TURTLE_BIND_EVENT(KeyboardEvent::Type(GLFW_KEY_S, GLFW_RELEASE, 0), OnBackwardReleased)

    TURTLE_BIND_EVENT(KeyboardEvent::Type(GLFW_KEY_D, GLFW_PRESS, 0), OnRightPressed)
    TURTLE_BIND_EVENT(KeyboardEvent::Type(GLFW_KEY_D, GLFW_RELEASE, 0), OnRightReleased)

    TURTLE_BIND_EVENT(KeyboardEvent::Type(GLFW_KEY_A, GLFW_PRESS, 0), OnLeftPressed)
    TURTLE_BIND_EVENT(KeyboardEvent::Type(GLFW_KEY_A, GLFW_RELEASE, 0), OnLeftReleased)
}

void Turtle::Camera::Update()
{
    _position += GetVelocity();

    _view = glm::lookAt(_position, _position + _orientation, _up);
    _projection = glm::perspective(glm::radians(_FOVdeg), static_cast<float>(_width) / static_cast<float>(_height), _nearPlane, _farPlane);
}

glm::vec3 Turtle::Camera::GetRightVector() const
{
    return glm::normalize(glm::cross(_orientation, _up));
}

void Turtle::Camera::OnRightMouseButtonClick(void* event)
{
    _canMove = true;
    _canLook = true;
    glfwSetCursorPos(_window->GetGlfwWindow(), (_width / 2), (_height / 2));
    glfwSetInputMode(_window->GetGlfwWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Turtle::Camera::OnRightMouseButtonRelease(void* event)
{
    _canMove = false;
    _canLook = false;
    glfwSetInputMode(_window->GetGlfwWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Turtle::Camera::OnForwardPressed(void* payload)
{
    _movingForward = true;
}

void Turtle::Camera::OnForwardReleased(void* payload)
{
    _movingForward = false;
}

void Turtle::Camera::OnBackwardPressed(void* payload)
{
    _movingBackward = true;
}

void Turtle::Camera::OnBackwardReleased(void* payload)
{
    _movingBackward = false;
}

void Turtle::Camera::OnRightPressed(void* payload)
{
    _movingRight = true;
}

void Turtle::Camera::OnRightReleased(void* payload)
{
    _movingRight = false;
}

void Turtle::Camera::OnLeftPressed(void* payload)
{
    _movingLeft = true;
}

void Turtle::Camera::OnLeftReleased(void* payload)
{
    _movingLeft = false;
}

void Turtle::Camera::OnMouseMoved(void* payload)
{
    const int32_t posX = *static_cast<int32_t*>(payload);
    const int32_t posY = *reinterpret_cast<int32_t*>(static_cast<char*>(payload) + sizeof(int32_t));

    if (!_canLook) return;

    const float rotX = _sensitivity * static_cast<float>(posY - (_height / 2)) / _height;
    const float rotY = _sensitivity * static_cast<float>(posX - (_width / 2)) / _width;

    const glm::vec3 newOrientation = glm::rotate(_orientation, glm::radians(-rotX), glm::normalize(glm::cross(_orientation, _up)));

    // Decides whether or not the next vertical Orientation is legal or not
    if (abs(glm::angle(newOrientation, _up) - glm::radians(90.0f)) <= glm::radians(85.0f) 
        && abs(glm::angle(newOrientation, -_up) - glm::radians(90.0f)) <= glm::radians(85.0f))
    {
        _orientation = newOrientation;
    }

    // Rotates the Orientation left and right
    _orientation = glm::rotate(_orientation, glm::radians(-rotY), _up);

    glfwSetCursorPos(_window->GetGlfwWindow(), (_width / 2), (_height / 2));
}