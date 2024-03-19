#pragma once

#include <glm/glm.hpp>
#include <functional>
#include <map>
#include "input/mouse.h"
#include "input/keyboard.h"


class Camera
{
    glm::vec3 position;
    glm::vec3 viewDirection;
    glm::vec3 up;

    std::map<int, input::Keyboard::key_state> keyPressedMap;

    const glm::vec3 MOVEMENT_SPEED_SCALE = { 0.01f, 0.01f, 0.01f };

public:
    Camera();

    glm::mat4 getWorldToViewMatrix() const;

    void mouseUpdate(const glm::vec2& mousePositionDelta);

    void moveForward(input::Keyboard::key_state keyState);
    void moveBackward(input::Keyboard::key_state keyState);
    void strafeLeft(input::Keyboard::key_state keyState);
    void strafeRight(input::Keyboard::key_state keyState);
    void moveUp(input::Keyboard::key_state keyState);
    void moveDown(input::Keyboard::key_state keyState);
    void movementUpdate();
    void keyboardUpdate(input::Keyboard::Event event);
};
