#include "camera.h"

#include "glm/ext.hpp"


Camera::Camera()
    : position(-1.0f, 1.0f, -1.0f),
    viewDirection(0.0f, -1.0f, -1.0f),
    up(0.0f, 1.0f, 0.0f)

{
    keyPressedMap =
    {
        { GLFW_KEY_W,{ GLFW_KEY_W, 0, std::bind(&Camera::moveForward, this, std::placeholders::_1) } },
        { GLFW_KEY_A,{ GLFW_KEY_A, 0, std::bind(&Camera::strafeLeft, this, std::placeholders::_1) } },
        { GLFW_KEY_S,{ GLFW_KEY_S, 0, std::bind(&Camera::moveBackward, this, std::placeholders::_1) } },
        { GLFW_KEY_D,{ GLFW_KEY_D, 0, std::bind(&Camera::strafeRight, this, std::placeholders::_1) } },
        { GLFW_KEY_SPACE,{ GLFW_KEY_SPACE, 0, std::bind(&Camera::moveUp, this, std::placeholders::_1) } },
        { GLFW_KEY_LEFT_SHIFT,{ GLFW_KEY_LEFT_SHIFT, 0, std::bind(&Camera::moveDown, this, std::placeholders::_1) } }
    };
}

void Camera::keyboardUpdate(input::Keyboard::Event event)
{
    auto iter = keyPressedMap.find(event.key);
    if (iter != keyPressedMap.end())
    {
        input::Keyboard::key_state& keyState = iter->second;

        keyState.state = event.action;
    }
}

void Camera::movementUpdate()
{
    for (auto& iter : keyPressedMap)
    {
        input::Keyboard::key_state& keyState = iter.second;
        if (keyState.state == GLFW_PRESS || keyState.state == GLFW_REPEAT)
        {
            keyState.actionWhenPressed(keyState);
        }
    }
}

void Camera::moveDown(input::Keyboard::key_state keyState)
{
    position = position + (up * glm::vec3(-MOVEMENT_SPEED_SCALE.y));
}

void Camera::moveForward(input::Keyboard::key_state keyState)
{
    position = position + (viewDirection * glm::vec3(MOVEMENT_SPEED_SCALE.z));
}

void Camera::moveBackward(input::Keyboard::key_state keyState)
{
    position = position + (viewDirection * glm::vec3(-MOVEMENT_SPEED_SCALE.z));
}

void Camera::strafeLeft(input::Keyboard::key_state keyState)
{
    glm::vec3 strafeDirection = glm::cross(viewDirection, up);
    position = position + (strafeDirection * glm::vec3(-MOVEMENT_SPEED_SCALE.x));
}

void Camera::strafeRight(input::Keyboard::key_state keyState)
{
    glm::vec3 strafeDirection = glm::cross(viewDirection, up);
    position = position + (strafeDirection * glm::vec3(MOVEMENT_SPEED_SCALE.x));
}

void Camera::moveUp(input::Keyboard::key_state keyState)
{
    position = position + (up * glm::vec3(MOVEMENT_SPEED_SCALE.y));
}

void Camera::mouseUpdate(const glm::vec2& mousePositionDelta)
{
    // Do nothing if delta is big to avoid annoyingness with out of window mouse movements
    if (glm::length(mousePositionDelta) > 50.0f)
    {
        return;
    }

    const float MOUSE_SENSITIVITY = -0.0025f;

    // Horizontal update
    viewDirection = glm::mat3(glm::rotate(glm::mat4(1), mousePositionDelta.x * MOUSE_SENSITIVITY, up)) * viewDirection;

    glm::vec3 toRotateAround = glm::cross(viewDirection, up);
    viewDirection = glm::mat3(glm::rotate(glm::mat4(1), mousePositionDelta.y * MOUSE_SENSITIVITY, toRotateAround)) * viewDirection;
}

glm::mat4 Camera::getWorldToViewMatrix() const
{
    return glm::lookAt(position, position + viewDirection, up);
    //return glm::lookAt(position, glm::vec3(0.0f, 0.0f, 0.0f), up);
}
