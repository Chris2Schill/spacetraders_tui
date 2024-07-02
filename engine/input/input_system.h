#pragma once

#include <glm/vec2.hpp>

#include "engine/input/coordinate_conversions.h"

class Scene;
namespace sf {
    class WindowBase;
}


struct InputSystem {
    enum MouseScroll { WHEEL_UP, WHEEL_DOWN };
    static Coord<ScreenSpace> get_mouse_position(const sf::WindowBase* win = nullptr);
    static void on_runtime_update(Scene* scene);
};
