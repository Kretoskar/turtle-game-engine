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

    if (!bCanMove)
    {
        return { 0.0f, 0.0f, 0.0f };
    }

    if (bMovingForward)
    {
        retVelocity += Orientation * speed;
    }
    if (bMovingBackward)
    {
        retVelocity -= Orientation * speed;
    }
    if (bMovingRight)
    {
        retVelocity += GetRightVector() * speed;
    }
    if (bMovingLeft)
    {
        retVelocity -= GetRightVector() * speed;
    }

    return retVelocity;
}

void Turtle::Camera::Init()
{
    width = Engine::EngineSettings->WindowSetting().Height;
    height = Engine::EngineSettings->WindowSetting().Width;

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
    Position += GetVelocity();

    view = glm::lookAt(Position, Position + Orientation, Up);
    projection = glm::perspective(glm::radians(FOVdeg), static_cast<float>(width) / static_cast<float>(height), nearPlane, farPlane);
}

glm::vec3 Turtle::Camera::GetRightVector() const
{
    return glm::normalize(glm::cross(Orientation, Up));
}

void Turtle::Camera::OnRightMouseButtonClick(void* event)
{
    bCanMove = true;
    bCanLook = true;
    glfwSetCursorPos(window->GetGlfwWindow(), (width / 2), (height / 2));
    glfwSetInputMode(window->GetGlfwWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Turtle::Camera::OnRightMouseButtonRelease(void* event)
{
    bCanMove = false;
    bCanLook = false;
    glfwSetInputMode(window->GetGlfwWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Turtle::Camera::OnForwardPressed(void* payload)
{
    bMovingForward = true;
}

void Turtle::Camera::OnForwardReleased(void* payload)
{
    bMovingForward = false;
}

void Turtle::Camera::OnBackwardPressed(void* payload)
{
    bMovingBackward = true;
}

void Turtle::Camera::OnBackwardReleased(void* payload)
{
    bMovingBackward = false;
}

void Turtle::Camera::OnRightPressed(void* payload)
{
    bMovingRight = true;
}

void Turtle::Camera::OnRightReleased(void* payload)
{
    bMovingRight = false;
}

void Turtle::Camera::OnLeftPressed(void* payload)
{
    bMovingLeft = true;
}

void Turtle::Camera::OnLeftReleased(void* payload)
{
    bMovingLeft = false;
}

void Turtle::Camera::OnMouseMoved(void* payload)
{
    const int posX = *static_cast<int*>(payload);
    const int posY = *reinterpret_cast<int*>(static_cast<char*>(payload) + sizeof(int));

    if (!bCanLook) return;

    const float rotX = sensitivity * static_cast<float>(posY - (height / 2)) / height;
    const float rotY = sensitivity * static_cast<float>(posX - (width / 2)) / width;

    const glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

    // Decides whether or not the next vertical Orientation is legal or not
    if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f) 
        && abs(glm::angle(newOrientation, -Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
    {
        Orientation = newOrientation;
    }

    // Rotates the Orientation left and right
    Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

    glfwSetCursorPos(window->GetGlfwWindow(), (width / 2), (height / 2));
}